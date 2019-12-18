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
struct ravb_private {int /*<<< orphan*/  lock; } ;
struct net_device {long flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int /*<<< orphan*/  ECMR_PRM ; 
 long IFF_PROMISC ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ravb_set_rx_mode(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	ravb_modify(ndev, ECMR, ECMR_PRM,
		    ndev->flags & IFF_PROMISC ? ECMR_PRM : 0);
	spin_unlock_irqrestore(&priv->lock, flags);
}