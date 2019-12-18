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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ feature_index; scalar_t__ funcindex_clientid; int /*<<< orphan*/  params; } ;
struct hidpp_report {TYPE_1__ fap; } ;
struct TYPE_4__ {scalar_t__ feature_index; int online; int capacity; int level; int status; scalar_t__ ps; } ;
struct hidpp_device {TYPE_2__ battery; } ;

/* Variables and functions */
 scalar_t__ EVENT_BATTERY_LEVEL_STATUS_BROADCAST ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int hidpp20_batterylevel_map_status_capacity (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  power_supply_changed (scalar_t__) ; 

__attribute__((used)) static int hidpp20_battery_event(struct hidpp_device *hidpp,
				 u8 *data, int size)
{
	struct hidpp_report *report = (struct hidpp_report *)data;
	int status, capacity, next_capacity, level;
	bool changed;

	if (report->fap.feature_index != hidpp->battery.feature_index ||
	    report->fap.funcindex_clientid != EVENT_BATTERY_LEVEL_STATUS_BROADCAST)
		return 0;

	status = hidpp20_batterylevel_map_status_capacity(report->fap.params,
							  &capacity,
							  &next_capacity,
							  &level);

	/* the capacity is only available when discharging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	changed = capacity != hidpp->battery.capacity ||
		  level != hidpp->battery.level ||
		  status != hidpp->battery.status;

	if (changed) {
		hidpp->battery.level = level;
		hidpp->battery.capacity = capacity;
		hidpp->battery.status = status;
		if (hidpp->battery.ps)
			power_supply_changed(hidpp->battery.ps);
	}

	return 0;
}