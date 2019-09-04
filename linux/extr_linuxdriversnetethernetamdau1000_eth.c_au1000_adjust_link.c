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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {scalar_t__ link; int speed; int duplex; } ;
struct net_device {struct phy_device* phydev; } ;
struct au1000_private {int old_speed; int old_duplex; scalar_t__ old_link; int /*<<< orphan*/  lock; TYPE_1__* mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  MAC_DISABLE_RX_OWN ; 
 int /*<<< orphan*/  MAC_FULL_DUPLEX ; 
#define  SPEED_10 129 
#define  SPEED_100 128 
 int /*<<< orphan*/  au1000_enable_rx_tx (struct net_device*) ; 
 int /*<<< orphan*/  au1000_hard_stop (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
au1000_adjust_link(struct net_device *dev)
{
	struct au1000_private *aup = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	unsigned long flags;
	u32 reg;

	int status_change = 0;

	BUG_ON(!phydev);

	spin_lock_irqsave(&aup->lock, flags);

	if (phydev->link && (aup->old_speed != phydev->speed)) {
		/* speed changed */

		switch (phydev->speed) {
		case SPEED_10:
		case SPEED_100:
			break;
		default:
			netdev_warn(dev, "Speed (%d) is not 10/100 ???\n",
							phydev->speed);
			break;
		}

		aup->old_speed = phydev->speed;

		status_change = 1;
	}

	if (phydev->link && (aup->old_duplex != phydev->duplex)) {
		/* duplex mode changed */

		/* switching duplex mode requires to disable rx and tx! */
		au1000_hard_stop(dev);

		reg = readl(&aup->mac->control);
		if (DUPLEX_FULL == phydev->duplex) {
			reg |= MAC_FULL_DUPLEX;
			reg &= ~MAC_DISABLE_RX_OWN;
		} else {
			reg &= ~MAC_FULL_DUPLEX;
			reg |= MAC_DISABLE_RX_OWN;
		}
		writel(reg, &aup->mac->control);
		wmb(); /* drain writebuffer */
		mdelay(1);

		au1000_enable_rx_tx(dev);
		aup->old_duplex = phydev->duplex;

		status_change = 1;
	}

	if (phydev->link != aup->old_link) {
		/* link state changed */

		if (!phydev->link) {
			/* link went down */
			aup->old_speed = 0;
			aup->old_duplex = -1;
		}

		aup->old_link = phydev->link;
		status_change = 1;
	}

	spin_unlock_irqrestore(&aup->lock, flags);

	if (status_change) {
		if (phydev->link)
			netdev_info(dev, "link up (%d/%s)\n",
			       phydev->speed,
			       DUPLEX_FULL == phydev->duplex ? "Full" : "Half");
		else
			netdev_info(dev, "link down\n");
	}
}