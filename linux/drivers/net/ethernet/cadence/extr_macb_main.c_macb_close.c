#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ phydev; } ;
struct macb_queue {int /*<<< orphan*/  napi; } ;
struct macb {unsigned int num_queues; TYPE_2__* pdev; TYPE_1__* ptp_info; int /*<<< orphan*/  lock; struct macb_queue* queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ptp_remove ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  macb_free_consistent (struct macb*) ; 
 int /*<<< orphan*/  macb_reset_hw (struct macb*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static int macb_close(struct net_device *dev)
{
	struct macb *bp = netdev_priv(dev);
	struct macb_queue *queue;
	unsigned long flags;
	unsigned int q;

	netif_tx_stop_all_queues(dev);

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue)
		napi_disable(&queue->napi);

	if (dev->phydev)
		phy_stop(dev->phydev);

	spin_lock_irqsave(&bp->lock, flags);
	macb_reset_hw(bp);
	netif_carrier_off(dev);
	spin_unlock_irqrestore(&bp->lock, flags);

	macb_free_consistent(bp);

	if (bp->ptp_info)
		bp->ptp_info->ptp_remove(dev);

	pm_runtime_put(&bp->pdev->dev);

	return 0;
}