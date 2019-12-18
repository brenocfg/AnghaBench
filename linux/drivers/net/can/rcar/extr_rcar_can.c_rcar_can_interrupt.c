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
typedef  int u8 ;
struct rcar_can_priv {int ier; int /*<<< orphan*/  napi; TYPE_1__* regs; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ier; int /*<<< orphan*/  isr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RCAR_CAN_IER_RXFIE ; 
 int RCAR_CAN_ISR_ERSF ; 
 int RCAR_CAN_ISR_RXFF ; 
 int RCAR_CAN_ISR_TXFF ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct rcar_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcar_can_error (struct net_device*) ; 
 int /*<<< orphan*/  rcar_can_tx_done (struct net_device*) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rcar_can_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = dev_id;
	struct rcar_can_priv *priv = netdev_priv(ndev);
	u8 isr;

	isr = readb(&priv->regs->isr);
	if (!(isr & priv->ier))
		return IRQ_NONE;

	if (isr & RCAR_CAN_ISR_ERSF)
		rcar_can_error(ndev);

	if (isr & RCAR_CAN_ISR_TXFF)
		rcar_can_tx_done(ndev);

	if (isr & RCAR_CAN_ISR_RXFF) {
		if (napi_schedule_prep(&priv->napi)) {
			/* Disable Rx FIFO interrupts */
			priv->ier &= ~RCAR_CAN_IER_RXFIE;
			writeb(priv->ier, &priv->regs->ier);
			__napi_schedule(&priv->napi);
		}
	}

	return IRQ_HANDLED;
}