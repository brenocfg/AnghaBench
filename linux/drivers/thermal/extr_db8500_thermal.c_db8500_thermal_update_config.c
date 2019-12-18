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
typedef  int /*<<< orphan*/  u8 ;
struct db8500_thermal_zone {unsigned int cur_index; unsigned long interpolated_temp; int trend; } ;
typedef  enum thermal_trend { ____Placeholder_thermal_trend } thermal_trend ;

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_DEFAULT_MEASURE_TIME ; 
 int /*<<< orphan*/  prcmu_config_hotmon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcmu_start_temp_sense (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcmu_stop_temp_sense () ; 

__attribute__((used)) static void db8500_thermal_update_config(struct db8500_thermal_zone *th,
					 unsigned int idx,
					 enum thermal_trend trend,
					 unsigned long next_low,
					 unsigned long next_high)
{
	prcmu_stop_temp_sense();

	th->cur_index = idx;
	th->interpolated_temp = (next_low + next_high)/2;
	th->trend = trend;

	/*
	 * The PRCMU accept absolute temperatures in celsius so divide
	 * down the millicelsius with 1000
	 */
	prcmu_config_hotmon((u8)(next_low/1000), (u8)(next_high/1000));
	prcmu_start_temp_sense(PRCMU_DEFAULT_MEASURE_TIME);
}