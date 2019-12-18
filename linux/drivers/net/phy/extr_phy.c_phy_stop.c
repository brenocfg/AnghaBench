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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct phy_device {TYPE_1__ state_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_HALTED ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_is_started (struct phy_device*) ; 
 int /*<<< orphan*/  phy_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_state_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop_machine (struct phy_device*) ; 

void phy_stop(struct phy_device *phydev)
{
	if (!phy_is_started(phydev)) {
		WARN(1, "called from state %s\n",
		     phy_state_to_str(phydev->state));
		return;
	}

	mutex_lock(&phydev->lock);

	phydev->state = PHY_HALTED;

	mutex_unlock(&phydev->lock);

	phy_state_machine(&phydev->state_queue.work);
	phy_stop_machine(phydev);

	/* Cannot call flush_scheduled_work() here as desired because
	 * of rtnl_lock(), but PHY_HALTED shall guarantee irq handler
	 * will not reenable interrupts.
	 */
}