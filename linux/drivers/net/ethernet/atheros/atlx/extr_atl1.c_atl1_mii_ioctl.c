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
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;
struct atl1_adapter {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int EINVAL ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int atl1_mii_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	unsigned long flags;
	int retval;

	if (!netif_running(netdev))
		return -EINVAL;

	spin_lock_irqsave(&adapter->lock, flags);
	retval = generic_mii_ioctl(&adapter->mii, if_mii(ifr), cmd, NULL);
	spin_unlock_irqrestore(&adapter->lock, flags);

	return retval;
}