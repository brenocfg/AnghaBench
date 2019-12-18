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
struct phy_device {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ PHY_HALTED ; 
 scalar_t__ PHY_READY ; 
 scalar_t__ PHY_UP ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __phy_resume (struct phy_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_start_machine (struct phy_device*) ; 
 int /*<<< orphan*/  phy_state_to_str (scalar_t__) ; 

void phy_start(struct phy_device *phydev)
{
	mutex_lock(&phydev->lock);

	if (phydev->state != PHY_READY && phydev->state != PHY_HALTED) {
		WARN(1, "called from state %s\n",
		     phy_state_to_str(phydev->state));
		goto out;
	}

	/* if phy was suspended, bring the physical link up again */
	__phy_resume(phydev);

	phydev->state = PHY_UP;

	phy_start_machine(phydev);
out:
	mutex_unlock(&phydev->lock);
}