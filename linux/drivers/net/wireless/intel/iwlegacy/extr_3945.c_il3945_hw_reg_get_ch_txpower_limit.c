#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_power_avg; } ;
struct TYPE_3__ {scalar_t__ max_power; } ;
struct il_channel_info {int max_power_avg; TYPE_2__ eeprom; TYPE_1__ tgd_data; } ;
typedef  int s8 ;

/* Variables and functions */
 int min (int,int) ; 

__attribute__((used)) static int
il3945_hw_reg_get_ch_txpower_limit(struct il_channel_info *ch_info)
{
	s8 max_power;

#if 0
	/* if we're using TGd limits, use lower of TGd or EEPROM */
	if (ch_info->tgd_data.max_power != 0)
		max_power =
		    min(ch_info->tgd_data.max_power,
			ch_info->eeprom.max_power_avg);

	/* else just use EEPROM limits */
	else
#endif
		max_power = ch_info->eeprom.max_power_avg;

	return min(max_power, ch_info->max_power_avg);
}