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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ifreq {int dummy; } ;
struct b44 {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_if; } ;

/* Variables and functions */
 int B44_FLAG_EXTERNAL_PHY ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ ,struct ifreq*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b44_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct b44 *bp = netdev_priv(dev);
	int err = -EINVAL;

	if (!netif_running(dev))
		goto out;

	spin_lock_irq(&bp->lock);
	if (bp->flags & B44_FLAG_EXTERNAL_PHY) {
		BUG_ON(!dev->phydev);
		err = phy_mii_ioctl(dev->phydev, ifr, cmd);
	} else {
		err = generic_mii_ioctl(&bp->mii_if, if_mii(ifr), cmd, NULL);
	}
	spin_unlock_irq(&bp->lock);
out:
	return err;
}