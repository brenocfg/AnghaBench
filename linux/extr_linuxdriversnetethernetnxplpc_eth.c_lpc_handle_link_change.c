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
struct phy_device {scalar_t__ link; scalar_t__ speed; int duplex; } ;
struct netdata_local {scalar_t__ speed; int duplex; scalar_t__ link; int /*<<< orphan*/  lock; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lpc_params_setup (struct netdata_local*) ; 
 struct netdata_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lpc_handle_link_change(struct net_device *ndev)
{
	struct netdata_local *pldat = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;
	unsigned long flags;

	bool status_change = false;

	spin_lock_irqsave(&pldat->lock, flags);

	if (phydev->link) {
		if ((pldat->speed != phydev->speed) ||
		    (pldat->duplex != phydev->duplex)) {
			pldat->speed = phydev->speed;
			pldat->duplex = phydev->duplex;
			status_change = true;
		}
	}

	if (phydev->link != pldat->link) {
		if (!phydev->link) {
			pldat->speed = 0;
			pldat->duplex = -1;
		}
		pldat->link = phydev->link;

		status_change = true;
	}

	spin_unlock_irqrestore(&pldat->lock, flags);

	if (status_change)
		__lpc_params_setup(pldat);
}