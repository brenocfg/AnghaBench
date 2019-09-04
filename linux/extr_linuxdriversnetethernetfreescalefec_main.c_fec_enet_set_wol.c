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
struct net_device {int /*<<< orphan*/  dev; } ;
struct fec_enet_private {int wol_flag; scalar_t__* irq; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int EINVAL ; 
 int FEC_WOL_FLAG_ENABLE ; 
 int FEC_WOL_HAS_MAGIC_PACKET ; 
 int WAKE_MAGIC ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  disable_irq_wake (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq_wake (scalar_t__) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
fec_enet_set_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	if (!(fep->wol_flag & FEC_WOL_HAS_MAGIC_PACKET))
		return -EINVAL;

	if (wol->wolopts & ~WAKE_MAGIC)
		return -EINVAL;

	device_set_wakeup_enable(&ndev->dev, wol->wolopts & WAKE_MAGIC);
	if (device_may_wakeup(&ndev->dev)) {
		fep->wol_flag |= FEC_WOL_FLAG_ENABLE;
		if (fep->irq[0] > 0)
			enable_irq_wake(fep->irq[0]);
	} else {
		fep->wol_flag &= (~FEC_WOL_FLAG_ENABLE);
		if (fep->irq[0] > 0)
			disable_irq_wake(fep->irq[0]);
	}

	return 0;
}