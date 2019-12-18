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
struct nct7904_data {int fanin_mask; } ;

/* Variables and functions */
#define  hwmon_fan_alarm 130 
#define  hwmon_fan_input 129 
#define  hwmon_fan_min 128 

__attribute__((used)) static umode_t nct7904_fan_is_visible(const void *_data, u32 attr, int channel)
{
	const struct nct7904_data *data = _data;

	switch (attr) {
	case hwmon_fan_input:
	case hwmon_fan_alarm:
		if (data->fanin_mask & (1 << channel))
			return 0444;
		break;
	case hwmon_fan_min:
		if (data->fanin_mask & (1 << channel))
			return 0644;
		break;
	default:
		break;
	}

	return 0;
}