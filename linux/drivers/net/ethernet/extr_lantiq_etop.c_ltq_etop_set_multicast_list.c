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
struct net_device {int flags; } ;
struct ltq_etop_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETOP_FTCU ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  LTQ_ETOP_ENETS0 ; 
 int /*<<< orphan*/  ltq_etop_w32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ltq_etop_set_multicast_list(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	unsigned long flags;

	/* ensure that the unicast filter is not enabled in promiscious mode */
	spin_lock_irqsave(&priv->lock, flags);
	if ((dev->flags & IFF_PROMISC) || (dev->flags & IFF_ALLMULTI))
		ltq_etop_w32_mask(ETOP_FTCU, 0, LTQ_ETOP_ENETS0);
	else
		ltq_etop_w32_mask(0, ETOP_FTCU, LTQ_ETOP_ENETS0);
	spin_unlock_irqrestore(&priv->lock, flags);
}