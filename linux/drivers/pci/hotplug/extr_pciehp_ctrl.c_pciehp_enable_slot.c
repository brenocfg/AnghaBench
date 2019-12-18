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
struct controller {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; TYPE_1__* pcie; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* port; } ;

/* Variables and functions */
 scalar_t__ ATTN_BUTTN (struct controller*) ; 
 int /*<<< orphan*/  INDICATOR_NOOP ; 
 int /*<<< orphan*/  OFF_STATE ; 
 int /*<<< orphan*/  ON_STATE ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL_PWR_IND_OFF ; 
 int __pciehp_enable_slot (struct controller*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_set_indicators (struct controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pciehp_enable_slot(struct controller *ctrl)
{
	int ret;

	pm_runtime_get_sync(&ctrl->pcie->port->dev);
	ret = __pciehp_enable_slot(ctrl);
	if (ret && ATTN_BUTTN(ctrl))
		/* may be blinking */
		pciehp_set_indicators(ctrl, PCI_EXP_SLTCTL_PWR_IND_OFF,
				      INDICATOR_NOOP);
	pm_runtime_put(&ctrl->pcie->port->dev);

	mutex_lock(&ctrl->state_lock);
	ctrl->state = ret ? OFF_STATE : ON_STATE;
	mutex_unlock(&ctrl->state_lock);

	return ret;
}