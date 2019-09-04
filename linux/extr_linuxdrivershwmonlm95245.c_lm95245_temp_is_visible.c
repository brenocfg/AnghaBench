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
#define  hwmon_temp_crit 137 
#define  hwmon_temp_crit_alarm 136 
#define  hwmon_temp_crit_hyst 135 
#define  hwmon_temp_fault 134 
#define  hwmon_temp_input 133 
#define  hwmon_temp_max 132 
#define  hwmon_temp_max_alarm 131 
#define  hwmon_temp_max_hyst 130 
#define  hwmon_temp_offset 129 
#define  hwmon_temp_type 128 

__attribute__((used)) static umode_t lm95245_temp_is_visible(const void *data, u32 attr, int channel)
{
	switch (attr) {
	case hwmon_temp_input:
	case hwmon_temp_max_alarm:
	case hwmon_temp_max_hyst:
	case hwmon_temp_crit_alarm:
	case hwmon_temp_fault:
		return S_IRUGO;
	case hwmon_temp_type:
	case hwmon_temp_max:
	case hwmon_temp_crit:
	case hwmon_temp_offset:
		return S_IRUGO | S_IWUSR;
	case hwmon_temp_crit_hyst:
		return (channel == 0) ? S_IRUGO | S_IWUSR : S_IRUGO;
	default:
		return 0;
	}
}