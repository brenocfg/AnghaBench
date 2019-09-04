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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct ltq_etop_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_ETOP_MAC_DA0 ; 
 int /*<<< orphan*/  LTQ_ETOP_MAC_DA1 ; 
 int eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  ltq_etop_w32 (int,int /*<<< orphan*/ ) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
ltq_etop_set_mac_address(struct net_device *dev, void *p)
{
	int ret = eth_mac_addr(dev, p);

	if (!ret) {
		struct ltq_etop_priv *priv = netdev_priv(dev);
		unsigned long flags;

		/* store the mac for the unicast filter */
		spin_lock_irqsave(&priv->lock, flags);
		ltq_etop_w32(*((u32 *)dev->dev_addr), LTQ_ETOP_MAC_DA0);
		ltq_etop_w32(*((u16 *)&dev->dev_addr[4]) << 16,
			LTQ_ETOP_MAC_DA1);
		spin_unlock_irqrestore(&priv->lock, flags);
	}
	return ret;
}