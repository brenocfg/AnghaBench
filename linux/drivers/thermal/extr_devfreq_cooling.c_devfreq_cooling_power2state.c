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
typedef  unsigned long u32 ;
struct thermal_zone_device {int dummy; } ;
struct thermal_cooling_device {struct devfreq_cooling_device* devdata; } ;
struct devfreq_dev_status {unsigned long current_frequency; unsigned long total_time; scalar_t__ busy_time; } ;
struct devfreq_cooling_device {unsigned long res_util; int freq_table_size; unsigned long* power_table; int capped_state; TYPE_1__* power_ops; struct devfreq* devfreq; } ;
struct devfreq {struct devfreq_dev_status last_status; } ;
typedef  unsigned long s32 ;
struct TYPE_2__ {scalar_t__ get_real_power; } ;

/* Variables and functions */
 unsigned long SCALE_ERROR_MITIGATION ; 
 unsigned long get_static_power (struct devfreq_cooling_device*,unsigned long) ; 
 int /*<<< orphan*/  trace_thermal_power_devfreq_limit (struct thermal_cooling_device*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int devfreq_cooling_power2state(struct thermal_cooling_device *cdev,
				       struct thermal_zone_device *tz,
				       u32 power, unsigned long *state)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	struct devfreq *df = dfc->devfreq;
	struct devfreq_dev_status *status = &df->last_status;
	unsigned long freq = status->current_frequency;
	unsigned long busy_time;
	s32 dyn_power;
	u32 static_power;
	s32 est_power;
	int i;

	if (dfc->power_ops->get_real_power) {
		/* Scale for resource utilization */
		est_power = power * dfc->res_util;
		est_power /= SCALE_ERROR_MITIGATION;
	} else {
		static_power = get_static_power(dfc, freq);

		dyn_power = power - static_power;
		dyn_power = dyn_power > 0 ? dyn_power : 0;

		/* Scale dynamic power for utilization */
		busy_time = status->busy_time ?: 1;
		est_power = (dyn_power * status->total_time) / busy_time;
	}

	/*
	 * Find the first cooling state that is within the power
	 * budget for dynamic power.
	 */
	for (i = 0; i < dfc->freq_table_size - 1; i++)
		if (est_power >= dfc->power_table[i])
			break;

	*state = i;
	dfc->capped_state = i;
	trace_thermal_power_devfreq_limit(cdev, freq, *state, power);
	return 0;
}