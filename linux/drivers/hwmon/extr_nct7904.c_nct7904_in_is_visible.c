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
struct nct7904_data {int vsen_mask; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  hwmon_in_alarm 131 
#define  hwmon_in_input 130 
#define  hwmon_in_max 129 
#define  hwmon_in_min 128 
 int* nct7904_chan_to_index ; 

__attribute__((used)) static umode_t nct7904_in_is_visible(const void *_data, u32 attr, int channel)
{
	const struct nct7904_data *data = _data;
	int index = nct7904_chan_to_index[channel];

	switch (attr) {
	case hwmon_in_input:
	case hwmon_in_alarm:
		if (channel > 0 && (data->vsen_mask & BIT(index)))
			return 0444;
		break;
	case hwmon_in_min:
	case hwmon_in_max:
		if (channel > 0 && (data->vsen_mask & BIT(index)))
			return 0644;
		break;
	default:
		break;
	}

	return 0;
}