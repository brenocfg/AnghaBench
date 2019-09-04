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
typedef  int u16 ;
struct bme680_calib {int par_h4; int par_h5; int par_h6; int par_h7; scalar_t__ par_h2; scalar_t__ par_h3; scalar_t__ par_h1; } ;
struct bme680_data {int t_fine; struct bme680_calib bme680; } ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static u32 bme680_compensate_humid(struct bme680_data *data,
				   u16 adc_humid)
{
	struct bme680_calib *calib = &data->bme680;
	s32 var1, var2, var3, var4, var5, var6, temp_scaled, calc_hum;

	temp_scaled = (data->t_fine * 5 + 128) >> 8;
	var1 = (adc_humid - ((s32) ((s32) calib->par_h1 * 16))) -
		(((temp_scaled * (s32) calib->par_h3) / 100) >> 1);
	var2 = ((s32) calib->par_h2 *
		(((temp_scaled * calib->par_h4) / 100) +
		 (((temp_scaled * ((temp_scaled * calib->par_h5) / 100))
		   >> 6) / 100) + (1 << 14))) >> 10;
	var3 = var1 * var2;
	var4 = calib->par_h6 << 7;
	var4 = (var4 + ((temp_scaled * calib->par_h7) / 100)) >> 4;
	var5 = ((var3 >> 14) * (var3 >> 14)) >> 10;
	var6 = (var4 * var5) >> 1;
	calc_hum = (((var3 + var6) >> 10) * 1000) >> 12;

	if (calc_hum > 100000) /* Cap at 100%rH */
		calc_hum = 100000;
	else if (calc_hum < 0)
		calc_hum = 0;

	return calc_hum;
}