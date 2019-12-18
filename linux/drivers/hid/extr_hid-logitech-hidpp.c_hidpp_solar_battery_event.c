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
typedef  int u8 ;
struct TYPE_3__ {int funcindex_clientid; scalar_t__ feature_index; int* params; } ;
struct hidpp_report {TYPE_1__ fap; } ;
struct TYPE_4__ {scalar_t__ solar_feature_index; int capacity; int online; int status; scalar_t__ ps; } ;
struct hidpp_device {TYPE_2__ battery; } ;

/* Variables and functions */
 int EVENT_SOLAR_BATTERY_BROADCAST ; 
#define  EVENT_SOLAR_BATTERY_LIGHT_MEASURE 129 
#define  EVENT_SOLAR_CHECK_LIGHT_BUTTON 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int /*<<< orphan*/  power_supply_changed (scalar_t__) ; 

__attribute__((used)) static int hidpp_solar_battery_event(struct hidpp_device *hidpp,
				     u8 *data, int size)
{
	struct hidpp_report *report = (struct hidpp_report *)data;
	int capacity, lux, status;
	u8 function;

	function = report->fap.funcindex_clientid;


	if (report->fap.feature_index != hidpp->battery.solar_feature_index ||
	    !(function == EVENT_SOLAR_BATTERY_BROADCAST ||
	      function == EVENT_SOLAR_BATTERY_LIGHT_MEASURE ||
	      function == EVENT_SOLAR_CHECK_LIGHT_BUTTON))
		return 0;

	capacity = report->fap.params[0];

	switch (function) {
	case EVENT_SOLAR_BATTERY_LIGHT_MEASURE:
		lux = (report->fap.params[1] << 8) | report->fap.params[2];
		if (lux > 200)
			status = POWER_SUPPLY_STATUS_CHARGING;
		else
			status = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case EVENT_SOLAR_CHECK_LIGHT_BUTTON:
	default:
		if (capacity < hidpp->battery.capacity)
			status = POWER_SUPPLY_STATUS_DISCHARGING;
		else
			status = POWER_SUPPLY_STATUS_CHARGING;

	}

	if (capacity == 100)
		status = POWER_SUPPLY_STATUS_FULL;

	hidpp->battery.online = true;
	if (capacity != hidpp->battery.capacity ||
	    status != hidpp->battery.status) {
		hidpp->battery.capacity = capacity;
		hidpp->battery.status = status;
		if (hidpp->battery.ps)
			power_supply_changed(hidpp->battery.ps);
	}

	return 0;
}