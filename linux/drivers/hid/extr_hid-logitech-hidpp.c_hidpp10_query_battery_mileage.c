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
struct TYPE_3__ {int /*<<< orphan*/ * params; } ;
struct hidpp_report {TYPE_1__ rap; } ;
struct TYPE_4__ {int status; int online; int /*<<< orphan*/  capacity; } ;
struct hidpp_device {TYPE_2__ battery; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDPP_GET_REGISTER ; 
 int /*<<< orphan*/  HIDPP_REG_BATTERY_MILEAGE ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int /*<<< orphan*/  REPORT_ID_HIDPP_SHORT ; 
 int hidpp10_battery_mileage_map_status (int /*<<< orphan*/ ) ; 
 int hidpp_send_rap_command_sync (struct hidpp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hidpp_report*) ; 

__attribute__((used)) static int hidpp10_query_battery_mileage(struct hidpp_device *hidpp)
{
	struct hidpp_report response;
	int ret, status;

	ret = hidpp_send_rap_command_sync(hidpp,
					REPORT_ID_HIDPP_SHORT,
					HIDPP_GET_REGISTER,
					HIDPP_REG_BATTERY_MILEAGE,
					NULL, 0, &response);
	if (ret)
		return ret;

	hidpp->battery.capacity = response.rap.params[0];
	status = hidpp10_battery_mileage_map_status(response.rap.params[2]);
	hidpp->battery.status = status;
	/* the capacity is only available when discharging or full */
	hidpp->battery.online = status == POWER_SUPPLY_STATUS_DISCHARGING ||
				status == POWER_SUPPLY_STATUS_FULL;

	return 0;
}