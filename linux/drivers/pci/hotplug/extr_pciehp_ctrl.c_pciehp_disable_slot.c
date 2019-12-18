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
struct controller {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; TYPE_2__* pcie; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFF_STATE ; 
 int __pciehp_disable_slot (struct controller*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pciehp_disable_slot(struct controller *ctrl, bool safe_removal)
{
	int ret;

	pm_runtime_get_sync(&ctrl->pcie->port->dev);
	ret = __pciehp_disable_slot(ctrl, safe_removal);
	pm_runtime_put(&ctrl->pcie->port->dev);

	mutex_lock(&ctrl->state_lock);
	ctrl->state = OFF_STATE;
	mutex_unlock(&ctrl->state_lock);

	return ret;
}