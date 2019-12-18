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
struct bme680_calib {int par_p6; int par_p5; int par_p4; int par_p3; int par_p2; int par_p1; int par_p9; int par_p8; int par_p10; int par_p7; } ;
struct bme680_data {int t_fine; struct bme680_calib bme680; } ;
typedef  int s32 ;

/* Variables and functions */
 int BME680_MAX_OVERFLOW_VAL ; 

__attribute__((used)) static u32 bme680_compensate_press(struct bme680_data *data,
				   u32 adc_press)
{
	struct bme680_calib *calib = &data->bme680;
	s32 var1, var2, var3, press_comp;

	var1 = (data->t_fine >> 1) - 64000;
	var2 = ((((var1 >> 2) * (var1 >> 2)) >> 11) * calib->par_p6) >> 2;
	var2 = var2 + (var1 * calib->par_p5 << 1);
	var2 = (var2 >> 2) + (calib->par_p4 << 16);
	var1 = (((((var1 >> 2) * (var1 >> 2)) >> 13) *
			(calib->par_p3 << 5)) >> 3) +
			((calib->par_p2 * var1) >> 1);
	var1 = var1 >> 18;
	var1 = ((32768 + var1) * calib->par_p1) >> 15;
	press_comp = 1048576 - adc_press;
	press_comp = ((press_comp - (var2 >> 12)) * 3125);

	if (press_comp >= BME680_MAX_OVERFLOW_VAL)
		press_comp = ((press_comp / (u32)var1) << 1);
	else
		press_comp = ((press_comp << 1) / (u32)var1);

	var1 = (calib->par_p9 * (((press_comp >> 3) *
			(press_comp >> 3)) >> 13)) >> 12;
	var2 = ((press_comp >> 2) * calib->par_p8) >> 13;
	var3 = ((press_comp >> 8) * (press_comp >> 8) *
			(press_comp >> 8) * calib->par_p10) >> 17;

	press_comp += (var1 + var2 + var3 + (calib->par_p7 << 7)) >> 4;

	return press_comp;
}