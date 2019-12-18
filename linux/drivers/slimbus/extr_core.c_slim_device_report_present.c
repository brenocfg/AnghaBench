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
struct slim_eaddr {int dummy; } ;
struct slim_device {int /*<<< orphan*/  laddr; scalar_t__ is_laddr_valid; } ;
struct TYPE_2__ {scalar_t__ clk_state; } ;
struct slim_controller {int /*<<< orphan*/  dev; TYPE_1__ sched; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct slim_device*) ; 
 scalar_t__ SLIM_CLK_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int slim_device_alloc_laddr (struct slim_device*,int) ; 
 struct slim_device* slim_get_device (struct slim_controller*,struct slim_eaddr*) ; 

int slim_device_report_present(struct slim_controller *ctrl,
			       struct slim_eaddr *e_addr, u8 *laddr)
{
	struct slim_device *sbdev;
	int ret;

	ret = pm_runtime_get_sync(ctrl->dev);

	if (ctrl->sched.clk_state != SLIM_CLK_ACTIVE) {
		dev_err(ctrl->dev, "slim ctrl not active,state:%d, ret:%d\n",
				    ctrl->sched.clk_state, ret);
		goto slimbus_not_active;
	}

	sbdev = slim_get_device(ctrl, e_addr);
	if (IS_ERR(sbdev))
		return -ENODEV;

	if (sbdev->is_laddr_valid) {
		*laddr = sbdev->laddr;
		return 0;
	}

	ret = slim_device_alloc_laddr(sbdev, true);

slimbus_not_active:
	pm_runtime_mark_last_busy(ctrl->dev);
	pm_runtime_put_autosuspend(ctrl->dev);
	return ret;
}