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
struct nct7904_data {int tcpu_mask; int has_dts; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  hwmon_temp_alarm 134 
#define  hwmon_temp_crit 133 
#define  hwmon_temp_crit_hyst 132 
#define  hwmon_temp_input 131 
#define  hwmon_temp_max 130 
#define  hwmon_temp_max_hyst 129 
#define  hwmon_temp_type 128 

__attribute__((used)) static umode_t nct7904_temp_is_visible(const void *_data, u32 attr, int channel)
{
	const struct nct7904_data *data = _data;

	switch (attr) {
	case hwmon_temp_input:
	case hwmon_temp_alarm:
	case hwmon_temp_type:
		if (channel < 5) {
			if (data->tcpu_mask & BIT(channel))
				return 0444;
		} else {
			if (data->has_dts & BIT(channel - 5))
				return 0444;
		}
		break;
	case hwmon_temp_max:
	case hwmon_temp_max_hyst:
	case hwmon_temp_crit:
	case hwmon_temp_crit_hyst:
		if (channel < 5) {
			if (data->tcpu_mask & BIT(channel))
				return 0644;
		} else {
			if (data->has_dts & BIT(channel - 5))
				return 0644;
		}
		break;
	default:
		break;
	}

	return 0;
}