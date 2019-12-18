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
struct cdns3 {int role; int /*<<< orphan*/  dev; scalar_t__ role_override; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 int cdns3_role_start (struct cdns3*,int) ; 
 int /*<<< orphan*/  cdns3_role_stop (struct cdns3*) ; 
 int cdsn3_hw_role_state_machine (struct cdns3*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

int cdns3_hw_role_switch(struct cdns3 *cdns)
{
	enum usb_role real_role, current_role;
	int ret = 0;

	/* Do nothing if role based on syfs. */
	if (cdns->role_override)
		return 0;

	pm_runtime_get_sync(cdns->dev);

	current_role = cdns->role;
	real_role = cdsn3_hw_role_state_machine(cdns);

	/* Do nothing if nothing changed */
	if (current_role == real_role)
		goto exit;

	cdns3_role_stop(cdns);

	dev_dbg(cdns->dev, "Switching role %d -> %d", current_role, real_role);

	ret = cdns3_role_start(cdns, real_role);
	if (ret) {
		/* Back to current role */
		dev_err(cdns->dev, "set %d has failed, back to %d\n",
			real_role, current_role);
		ret = cdns3_role_start(cdns, current_role);
		if (ret)
			dev_err(cdns->dev, "back to %d failed too\n",
				current_role);
	}
exit:
	pm_runtime_put_sync(cdns->dev);
	return ret;
}