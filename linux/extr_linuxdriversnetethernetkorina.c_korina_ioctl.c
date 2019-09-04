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
struct mii_ioctl_data {int dummy; } ;
struct korina_private {int /*<<< orphan*/  mii_if; int /*<<< orphan*/  lock; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int,int /*<<< orphan*/ *) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  korina_set_carrier (int /*<<< orphan*/ *) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int korina_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct korina_private *lp = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(rq);
	int rc;

	if (!netif_running(dev))
		return -EINVAL;
	spin_lock_irq(&lp->lock);
	rc = generic_mii_ioctl(&lp->mii_if, data, cmd, NULL);
	spin_unlock_irq(&lp->lock);
	korina_set_carrier(&lp->mii_if);

	return rc;
}