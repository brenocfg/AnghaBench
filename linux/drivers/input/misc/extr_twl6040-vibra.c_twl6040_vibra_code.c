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
typedef  int u8 ;

/* Variables and functions */
 int TWL6040_VIBDAT_MAX ; 
 int TWL6040_VIBRA_MOD ; 
 int USHRT_MAX ; 

__attribute__((used)) static u8 twl6040_vibra_code(int vddvib, int vibdrv_res, int motor_res,
			     int speed, int direction)
{
	int vpk, max_code;
	u8 vibdat;

	/* output swing */
	vpk = (vddvib * motor_res * TWL6040_VIBRA_MOD) /
		(100 * (vibdrv_res + motor_res));

	/* 50mV per VIBDAT code step */
	max_code = vpk / 50;
	if (max_code > TWL6040_VIBDAT_MAX)
		max_code = TWL6040_VIBDAT_MAX;

	/* scale speed to max allowed code */
	vibdat = (u8)((speed * max_code) / USHRT_MAX);

	/* 2's complement for direction > 180 degrees */
	vibdat *= direction;

	return vibdat;
}