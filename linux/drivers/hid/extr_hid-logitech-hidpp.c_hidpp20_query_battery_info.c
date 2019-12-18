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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int feature_index; int status; int capacity; int level; int online; } ;
struct hidpp_device {TYPE_1__ battery; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_PAGE_BATTERY_LEVEL_STATUS ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int hidpp20_batterylevel_get_battery_capacity (struct hidpp_device*,int,int*,int*,int*,int*) ; 
 int hidpp20_batterylevel_get_battery_info (struct hidpp_device*,int) ; 
 int hidpp_root_get_feature (struct hidpp_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidpp20_query_battery_info(struct hidpp_device *hidpp)
{
	u8 feature_type;
	int ret;
	int status, capacity, next_capacity, level;

	if (hidpp->battery.feature_index == 0xff) {
		ret = hidpp_root_get_feature(hidpp,
					     HIDPP_PAGE_BATTERY_LEVEL_STATUS,
					     &hidpp->battery.feature_index,
					     &feature_type);
		if (ret)
			return ret;
	}

	ret = hidpp20_batterylevel_get_battery_capacity(hidpp,
						hidpp->battery.feature_index,
						&status, &capacity,
						&next_capacity, &level);
	if (ret)
		return ret;

	ret = hidpp20_batterylevel_get_battery_info(hidpp,
						hidpp->battery.feature_index);
	if (ret)
		return ret;

	hidpp->battery.status = status;
	hidpp->battery.capacity = capacity;
	hidpp->battery.level = level;
	/* the capacity is only available when discharging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	return 0;
}