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
struct gb_control_intf_pm_response {int status; } ;
struct gb_control {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  response ;

/* Variables and functions */
 int GB_CONTROL_INTF_PM_OK ; 
 int /*<<< orphan*/  GB_CONTROL_TYPE_INTF_HIBERNATE_ABORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_control_interface_pm_status_map (int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_control_intf_pm_response*,int) ; 

int gb_control_interface_hibernate_abort(struct gb_control *control)
{
	struct gb_control_intf_pm_response response;
	int ret;

	ret = gb_operation_sync(control->connection,
				GB_CONTROL_TYPE_INTF_HIBERNATE_ABORT, NULL, 0,
				&response, sizeof(response));
	if (ret) {
		dev_err(&control->dev,
			"failed to send interface aborting hibernate: %d\n",
			ret);
		return ret;
	}

	if (response.status != GB_CONTROL_INTF_PM_OK) {
		dev_err(&control->dev, "interface error while aborting hibernate: %d\n",
			response.status);
		return gb_control_interface_pm_status_map(response.status);
	}

	return 0;
}