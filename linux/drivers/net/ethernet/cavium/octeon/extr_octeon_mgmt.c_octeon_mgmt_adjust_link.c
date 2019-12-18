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
struct phy_device {scalar_t__ link; scalar_t__ duplex; scalar_t__ speed; } ;
struct octeon_mgmt {scalar_t__ last_link; scalar_t__ last_duplex; scalar_t__ last_speed; int /*<<< orphan*/  lock; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  octeon_mgmt_disable_link (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  octeon_mgmt_enable_link (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  octeon_mgmt_update_link (struct octeon_mgmt*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void octeon_mgmt_adjust_link(struct net_device *netdev)
{
	struct octeon_mgmt *p = netdev_priv(netdev);
	struct phy_device *phydev = netdev->phydev;
	unsigned long flags;
	int link_changed = 0;

	if (!phydev)
		return;

	spin_lock_irqsave(&p->lock, flags);


	if (!phydev->link && p->last_link)
		link_changed = -1;

	if (phydev->link &&
	    (p->last_duplex != phydev->duplex ||
	     p->last_link != phydev->link ||
	     p->last_speed != phydev->speed)) {
		octeon_mgmt_disable_link(p);
		link_changed = 1;
		octeon_mgmt_update_link(p);
		octeon_mgmt_enable_link(p);
	}

	p->last_link = phydev->link;
	p->last_speed = phydev->speed;
	p->last_duplex = phydev->duplex;

	spin_unlock_irqrestore(&p->lock, flags);

	if (link_changed != 0) {
		if (link_changed > 0)
			netdev_info(netdev, "Link is up - %d/%s\n",
				    phydev->speed, phydev->duplex == DUPLEX_FULL ? "Full" : "Half");
		else
			netdev_info(netdev, "Link is down\n");
	}
}