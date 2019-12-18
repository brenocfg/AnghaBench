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
typedef  scalar_t__ u32 ;
struct thermal_zone_device {int dummy; } ;
struct thermal_cooling_device {struct devfreq_cooling_device* devdata; } ;
struct devfreq_cooling_device {unsigned long freq_table_size; unsigned long* freq_table; scalar_t__* power_table; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ get_static_power (struct devfreq_cooling_device*,unsigned long) ; 

__attribute__((used)) static int devfreq_cooling_state2power(struct thermal_cooling_device *cdev,
				       struct thermal_zone_device *tz,
				       unsigned long state,
				       u32 *power)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;
	unsigned long freq;
	u32 static_power;

	if (state >= dfc->freq_table_size)
		return -EINVAL;

	freq = dfc->freq_table[state];
	static_power = get_static_power(dfc, freq);

	*power = dfc->power_table[state] + static_power;
	return 0;
}