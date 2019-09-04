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
typedef  int umode_t ;
typedef  int u32 ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
#define  hwmon_temp_crit 140 
#define  hwmon_temp_crit_alarm 139 
#define  hwmon_temp_crit_hyst 138 
#define  hwmon_temp_emergency 137 
#define  hwmon_temp_emergency_alarm 136 
#define  hwmon_temp_emergency_hyst 135 
#define  hwmon_temp_fault 134 
#define  hwmon_temp_input 133 
#define  hwmon_temp_max 132 
#define  hwmon_temp_max_alarm 131 
#define  hwmon_temp_min 130 
#define  hwmon_temp_min_alarm 129 
#define  hwmon_temp_offset 128 

__attribute__((used)) static umode_t lm90_temp_is_visible(const void *data, u32 attr, int channel)
{
	switch (attr) {
	case hwmon_temp_input:
	case hwmon_temp_min_alarm:
	case hwmon_temp_max_alarm:
	case hwmon_temp_crit_alarm:
	case hwmon_temp_emergency_alarm:
	case hwmon_temp_emergency_hyst:
	case hwmon_temp_fault:
		return S_IRUGO;
	case hwmon_temp_min:
	case hwmon_temp_max:
	case hwmon_temp_crit:
	case hwmon_temp_emergency:
	case hwmon_temp_offset:
		return S_IRUGO | S_IWUSR;
	case hwmon_temp_crit_hyst:
		if (channel == 0)
			return S_IRUGO | S_IWUSR;
		return S_IRUGO;
	default:
		return 0;
	}
}