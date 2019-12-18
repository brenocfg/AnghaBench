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
struct bme680_calib {int par_t2; int par_t1; int par_t3; } ;
struct bme680_data {int t_fine; struct bme680_calib bme680; } ;
typedef  int s64 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  bme680_read_calib (struct bme680_data*,struct bme680_calib*) ; 

__attribute__((used)) static s16 bme680_compensate_temp(struct bme680_data *data,
				  s32 adc_temp)
{
	struct bme680_calib *calib = &data->bme680;
	s64 var1, var2, var3;
	s16 calc_temp;

	/* If the calibration is invalid, attempt to reload it */
	if (!calib->par_t2)
		bme680_read_calib(data, calib);

	var1 = (adc_temp >> 3) - (calib->par_t1 << 1);
	var2 = (var1 * calib->par_t2) >> 11;
	var3 = ((var1 >> 1) * (var1 >> 1)) >> 12;
	var3 = (var3 * (calib->par_t3 << 4)) >> 14;
	data->t_fine = var2 + var3;
	calc_temp = (data->t_fine * 5 + 128) >> 8;

	return calc_temp;
}