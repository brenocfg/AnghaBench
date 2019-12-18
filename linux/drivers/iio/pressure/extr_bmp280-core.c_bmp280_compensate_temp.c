#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bmp280_calib {scalar_t__ T3; scalar_t__ T1; scalar_t__ T2; } ;
struct TYPE_2__ {struct bmp280_calib bmp280; } ;
struct bmp280_data {int t_fine; TYPE_1__ calib; } ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static s32 bmp280_compensate_temp(struct bmp280_data *data,
				  s32 adc_temp)
{
	s32 var1, var2;
	struct bmp280_calib *calib = &data->calib.bmp280;

	var1 = (((adc_temp >> 3) - ((s32)calib->T1 << 1)) *
		((s32)calib->T2)) >> 11;
	var2 = (((((adc_temp >> 4) - ((s32)calib->T1)) *
		  ((adc_temp >> 4) - ((s32)calib->T1))) >> 12) *
		((s32)calib->T3)) >> 14;
	data->t_fine = var1 + var2;

	return (data->t_fine * 5 + 128) >> 8;
}