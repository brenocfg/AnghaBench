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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {scalar_t__ link; scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;
struct b44 {scalar_t__ old_link; int flags; } ;

/* Variables and functions */
 int B44_FLAG_FULL_DUPLEX ; 
 int /*<<< orphan*/  B44_TX_CTRL ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int /*<<< orphan*/  TX_CTRL_DUPLEX ; 
 int /*<<< orphan*/  br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void b44_adjust_link(struct net_device *dev)
{
	struct b44 *bp = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	bool status_changed = 0;

	BUG_ON(!phydev);

	if (bp->old_link != phydev->link) {
		status_changed = 1;
		bp->old_link = phydev->link;
	}

	/* reflect duplex change */
	if (phydev->link) {
		if ((phydev->duplex == DUPLEX_HALF) &&
		    (bp->flags & B44_FLAG_FULL_DUPLEX)) {
			status_changed = 1;
			bp->flags &= ~B44_FLAG_FULL_DUPLEX;
		} else if ((phydev->duplex == DUPLEX_FULL) &&
			   !(bp->flags & B44_FLAG_FULL_DUPLEX)) {
			status_changed = 1;
			bp->flags |= B44_FLAG_FULL_DUPLEX;
		}
	}

	if (status_changed) {
		u32 val = br32(bp, B44_TX_CTRL);
		if (bp->flags & B44_FLAG_FULL_DUPLEX)
			val |= TX_CTRL_DUPLEX;
		else
			val &= ~TX_CTRL_DUPLEX;
		bw32(bp, B44_TX_CTRL, val);
		phy_print_status(phydev);
	}
}