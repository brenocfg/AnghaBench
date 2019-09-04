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
struct net_device {struct phy_device* phydev; } ;
struct emac_board_info {scalar_t__ speed; int duplex; scalar_t__ link; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  emac_update_duplex (struct net_device*) ; 
 int /*<<< orphan*/  emac_update_speed (struct net_device*) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void emac_handle_link_change(struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	unsigned long flags;
	int status_change = 0;

	if (phydev->link) {
		if (db->speed != phydev->speed) {
			spin_lock_irqsave(&db->lock, flags);
			db->speed = phydev->speed;
			emac_update_speed(dev);
			spin_unlock_irqrestore(&db->lock, flags);
			status_change = 1;
		}

		if (db->duplex != phydev->duplex) {
			spin_lock_irqsave(&db->lock, flags);
			db->duplex = phydev->duplex;
			emac_update_duplex(dev);
			spin_unlock_irqrestore(&db->lock, flags);
			status_change = 1;
		}
	}

	if (phydev->link != db->link) {
		if (!phydev->link) {
			db->speed = 0;
			db->duplex = -1;
		}
		db->link = phydev->link;

		status_change = 1;
	}

	if (status_change)
		phy_print_status(phydev);
}