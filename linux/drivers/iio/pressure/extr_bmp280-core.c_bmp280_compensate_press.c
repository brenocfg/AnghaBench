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
typedef  int /*<<< orphan*/  u32 ;
struct bmp280_calib {scalar_t__ P7; scalar_t__ P8; scalar_t__ P9; scalar_t__ P1; scalar_t__ P2; scalar_t__ P3; scalar_t__ P4; scalar_t__ P5; scalar_t__ P6; } ;
struct TYPE_2__ {struct bmp280_calib bmp280; } ;
struct bmp280_data {scalar_t__ t_fine; TYPE_1__ calib; } ;
typedef  int s64 ;
typedef  int s32 ;

/* Variables and functions */
 int div64_s64 (int,int) ; 

__attribute__((used)) static u32 bmp280_compensate_press(struct bmp280_data *data,
				   s32 adc_press)
{
	s64 var1, var2, p;
	struct bmp280_calib *calib = &data->calib.bmp280;

	var1 = ((s64)data->t_fine) - 128000;
	var2 = var1 * var1 * (s64)calib->P6;
	var2 += (var1 * (s64)calib->P5) << 17;
	var2 += ((s64)calib->P4) << 35;
	var1 = ((var1 * var1 * (s64)calib->P3) >> 8) +
		((var1 * (s64)calib->P2) << 12);
	var1 = ((((s64)1) << 47) + var1) * ((s64)calib->P1) >> 33;

	if (var1 == 0)
		return 0;

	p = ((((s64)1048576 - adc_press) << 31) - var2) * 3125;
	p = div64_s64(p, var1);
	var1 = (((s64)calib->P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = ((s64)(calib->P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((s64)calib->P7) << 4);

	return (u32)p;
}