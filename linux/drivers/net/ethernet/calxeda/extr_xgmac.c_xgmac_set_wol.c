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
typedef  int u32 ;
struct xgmac_priv {int wolopts; int /*<<< orphan*/  device; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int WAKE_MAGIC ; 
 int WAKE_UCAST ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 struct xgmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int xgmac_set_wol(struct net_device *dev,
			      struct ethtool_wolinfo *wol)
{
	struct xgmac_priv *priv = netdev_priv(dev);
	u32 support = WAKE_MAGIC | WAKE_UCAST;

	if (!device_can_wakeup(priv->device))
		return -ENOTSUPP;

	if (wol->wolopts & ~support)
		return -EINVAL;

	priv->wolopts = wol->wolopts;

	if (wol->wolopts) {
		device_set_wakeup_enable(priv->device, 1);
		enable_irq_wake(dev->irq);
	} else {
		device_set_wakeup_enable(priv->device, 0);
		disable_irq_wake(dev->irq);
	}

	return 0;
}