#include "udf.h"

#define T_MIN 285.15
#define T_MAX 698.15
#define RHO_BASE(T) (1.4386e3 - 1.8711 * (T) + 2.737e-3 * (T) * (T) - 2.3793e-6 * (T) * (T) * (T))
#define RHO_NANO 3970.0
#define VOL_FRAC 0.01

DEFINE_PROPERTY(nanofluid_density, c, t)
{
    real T = C_T(c, t);
    real rho_base = 0.0;
    real rho_nano = RHO_NANO;
    real vol_frac = VOL_FRAC;
    real rho_nanofluid = 0.0;
    
    if (T < T_MIN ) {
        rho_base = 1072.43701; //temp=698.15
    }
    else if (T >= T_MIN && T <= T_MAX) {
        rho_base = RHO_BASE(T);
    }
    else if (T > T_MAX) {
        rho_base = 656.6956; //temp=698.15
    }

    rho_nanofluid = (1.0 - vol_frac) * rho_base + vol_frac * rho_nano;

    return rho_nanofluid;
}