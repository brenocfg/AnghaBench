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
struct phylink {int /*<<< orphan*/  resolve; int /*<<< orphan*/  state_mutex; struct phy_device* phydev; } ;
struct phy_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 

void phylink_disconnect_phy(struct phylink *pl)
{
	struct phy_device *phy;

	ASSERT_RTNL();

	phy = pl->phydev;
	if (phy) {
		mutex_lock(&phy->lock);
		mutex_lock(&pl->state_mutex);
		pl->phydev = NULL;
		mutex_unlock(&pl->state_mutex);
		mutex_unlock(&phy->lock);
		flush_work(&pl->resolve);

		phy_disconnect(phy);
	}
}