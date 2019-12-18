#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pending; } ;
struct softing_priv {TYPE_4__ tx; } ;
struct TYPE_6__ {int last_bus; scalar_t__ pending; } ;
struct TYPE_5__ {int /*<<< orphan*/  svc_count; } ;
struct softing {TYPE_3__* pdat; struct net_device** net; TYPE_2__ tx; int /*<<< orphan*/  spin; TYPE_1__ irq; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int nbus; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct net_device**) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TXMAX ; 
 scalar_t__ TX_ECHO_SKB_MAX ; 
 int /*<<< orphan*/  canif_is_active (struct net_device*) ; 
 struct softing_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ softing_handle_1 (struct softing*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t softing_irq_thread(int irq, void *dev_id)
{
	struct softing *card = (struct softing *)dev_id;
	struct net_device *netdev;
	struct softing_priv *priv;
	int j, offset, work_done;

	work_done = 0;
	spin_lock_bh(&card->spin);
	while (softing_handle_1(card) > 0) {
		++card->irq.svc_count;
		++work_done;
	}
	spin_unlock_bh(&card->spin);
	/* resume tx queue's */
	offset = card->tx.last_bus;
	for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
		if (card->tx.pending >= TXMAX)
			break;
		netdev = card->net[(j + offset + 1) % card->pdat->nbus];
		if (!netdev)
			continue;
		priv = netdev_priv(netdev);
		if (!canif_is_active(netdev))
			/* it makes no sense to wake dead busses */
			continue;
		if (priv->tx.pending >= TX_ECHO_SKB_MAX)
			continue;
		++work_done;
		netif_wake_queue(netdev);
	}
	return work_done ? IRQ_HANDLED : IRQ_NONE;
}