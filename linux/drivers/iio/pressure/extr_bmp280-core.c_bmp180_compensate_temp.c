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
struct bmp180_calib {int AC6; int AC5; int MC; int MD; } ;
struct TYPE_2__ {struct bmp180_calib bmp180; } ;
struct bmp280_data {int t_fine; TYPE_1__ calib; } ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static s32 bmp180_compensate_temp(struct bmp280_data *data, s32 adc_temp)
{
	s32 x1, x2;
	struct bmp180_calib *calib = &data->calib.bmp180;

	x1 = ((adc_temp - calib->AC6) * calib->AC5) >> 15;
	x2 = (calib->MC << 11) / (x1 + calib->MD);
	data->t_fine = x1 + x2;

	return (data->t_fine + 8) >> 4;
}