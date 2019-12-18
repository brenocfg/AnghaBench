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
struct stm_thermal_sensor {scalar_t__ base; int /*<<< orphan*/  low_temp; scalar_t__ low_temp_enabled; int /*<<< orphan*/  high_temp; } ;

/* Variables and functions */
 scalar_t__ DTS_ITR1_OFFSET ; 
 int TS1_HITTHD_MASK ; 
 int TS1_HITTHD_POS ; 
 int TS1_LITTHD_MASK ; 
 int readl_relaxed (scalar_t__) ; 
 int stm_thermal_calculate_threshold (struct stm_thermal_sensor*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm_thermal_set_threshold(struct stm_thermal_sensor *sensor)
{
	u32 value, th;
	int ret;

	value = readl_relaxed(sensor->base + DTS_ITR1_OFFSET);

	/* Erase threshold content */
	value &= ~(TS1_LITTHD_MASK | TS1_HITTHD_MASK);

	/* Retrieve the sample threshold number th for a given temperature */
	ret = stm_thermal_calculate_threshold(sensor, sensor->high_temp, &th);
	if (ret)
		return ret;

	value |= th & TS1_LITTHD_MASK;

	if (sensor->low_temp_enabled) {
		/* Retrieve the sample threshold */
		ret = stm_thermal_calculate_threshold(sensor, sensor->low_temp,
						      &th);
		if (ret)
			return ret;

		value |= (TS1_HITTHD_MASK  & (th << TS1_HITTHD_POS));
	}

	/* Write value on the Low interrupt threshold */
	writel_relaxed(value, sensor->base + DTS_ITR1_OFFSET);

	return 0;
}