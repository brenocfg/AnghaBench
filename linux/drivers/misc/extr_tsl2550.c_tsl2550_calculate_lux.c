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
typedef  size_t u8 ;
typedef  int u16 ;

/* Variables and functions */
 unsigned int TSL2550_MAX_LUX ; 
 int* count_lut ; 
 int* ratio_lut ; 

__attribute__((used)) static int tsl2550_calculate_lux(u8 ch0, u8 ch1)
{
	unsigned int lux;

	/* Look up count from channel values */
	u16 c0 = count_lut[ch0];
	u16 c1 = count_lut[ch1];

	/*
	 * Calculate ratio.
	 * Note: the "128" is a scaling factor
	 */
	u8 r = 128;

	/* Avoid division by 0 and count 1 cannot be greater than count 0 */
	if (c1 <= c0)
		if (c0) {
			r = c1 * 128 / c0;

			/* Calculate LUX */
			lux = ((c0 - c1) * ratio_lut[r]) / 256;
		} else
			lux = 0;
	else
		return 0;

	/* LUX range check */
	return lux > TSL2550_MAX_LUX ? TSL2550_MAX_LUX : lux;
}