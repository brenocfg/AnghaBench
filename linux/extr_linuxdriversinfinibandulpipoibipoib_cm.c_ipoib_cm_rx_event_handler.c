#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rx_flush_list; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; TYPE_1__ cm; } ;
struct ipoib_cm_rx {int /*<<< orphan*/  state; int /*<<< orphan*/  list; int /*<<< orphan*/  dev; } ;
struct ib_event {scalar_t__ event; } ;

/* Variables and functions */
 scalar_t__ IB_EVENT_QP_LAST_WQE_REACHED ; 
 int /*<<< orphan*/  IPOIB_CM_RX_FLUSH ; 
 int /*<<< orphan*/  ipoib_cm_start_rx_drain (struct ipoib_dev_priv*) ; 
 struct ipoib_dev_priv* ipoib_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipoib_cm_rx_event_handler(struct ib_event *event, void *ctx)
{
	struct ipoib_cm_rx *p = ctx;
	struct ipoib_dev_priv *priv = ipoib_priv(p->dev);
	unsigned long flags;

	if (event->event != IB_EVENT_QP_LAST_WQE_REACHED)
		return;

	spin_lock_irqsave(&priv->lock, flags);
	list_move(&p->list, &priv->cm.rx_flush_list);
	p->state = IPOIB_CM_RX_FLUSH;
	ipoib_cm_start_rx_drain(priv);
	spin_unlock_irqrestore(&priv->lock, flags);
}