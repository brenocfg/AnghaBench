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
struct net_device {int mtu; } ;
struct ltq_etop_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ETOP_PLEN_UNDER ; 
 int /*<<< orphan*/  LTQ_ETOP_IGPLEN ; 
 int /*<<< orphan*/  ltq_etop_w32 (int,int /*<<< orphan*/ ) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
ltq_etop_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	unsigned long flags;

	dev->mtu = new_mtu;

	spin_lock_irqsave(&priv->lock, flags);
	ltq_etop_w32((ETOP_PLEN_UNDER << 16) | new_mtu, LTQ_ETOP_IGPLEN);
	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}