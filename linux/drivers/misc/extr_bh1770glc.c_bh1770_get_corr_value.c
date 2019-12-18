#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct bh1770_chip {int lux_ga; int lux_cf; int lux_calib; } ;

/* Variables and functions */
 int BH1770_CALIB_SCALER ; 
 int BH1770_LUX_CF_SCALE ; 
 int BH1770_LUX_CORR_SCALE ; 
 int BH1770_LUX_GA_SCALE ; 

__attribute__((used)) static u32 bh1770_get_corr_value(struct bh1770_chip *chip)
{
	u32 tmp;
	/* Impact of glass attenuation correction */
	tmp = (BH1770_LUX_CORR_SCALE * chip->lux_ga) / BH1770_LUX_GA_SCALE;
	/* Impact of chip factor correction */
	tmp = (tmp * chip->lux_cf) / BH1770_LUX_CF_SCALE;
	/* Impact of Device specific calibration correction */
	tmp = (tmp * chip->lux_calib) / BH1770_CALIB_SCALER;
	return tmp;
}