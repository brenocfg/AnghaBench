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
struct ms5611_chip_info {int* prom; } ;
typedef  int s64 ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static int ms5607_temp_and_pressure_compensate(struct ms5611_chip_info *chip_info,
					       s32 *temp, s32 *pressure)
{
	s32 t = *temp, p = *pressure;
	s64 off, sens, dt;

	dt = t - (chip_info->prom[5] << 8);
	off = ((s64)chip_info->prom[2] << 17) + ((chip_info->prom[4] * dt) >> 6);
	sens = ((s64)chip_info->prom[1] << 16) + ((chip_info->prom[3] * dt) >> 7);

	t = 2000 + ((chip_info->prom[6] * dt) >> 23);
	if (t < 2000) {
		s64 off2, sens2, t2, tmp;

		t2 = (dt * dt) >> 31;
		tmp = (t - 2000) * (t - 2000);
		off2 = (61 * tmp) >> 4;
		sens2 = tmp << 1;

		if (t < -1500) {
			tmp = (t + 1500) * (t + 1500);
			off2 += 15 * tmp;
			sens2 += 8 * tmp;
		}

		t -= t2;
		off -= off2;
		sens -= sens2;
	}

	*temp = t;
	*pressure = (((p * sens) >> 21) - off) >> 15;

	return 0;
}