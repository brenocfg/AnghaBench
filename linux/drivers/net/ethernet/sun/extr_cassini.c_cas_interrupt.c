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
struct net_device {int dummy; } ;
struct cas {int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INTR_RX_DONE ; 
 int INTR_TX_ALL ; 
 int INTR_TX_INTME ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ REG_INTR_STATUS ; 
 int /*<<< orphan*/  cas_handle_irq (struct net_device*,struct cas*,int) ; 
 int /*<<< orphan*/  cas_mask_intr (struct cas*) ; 
 int /*<<< orphan*/  cas_rx_ringN (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_tx (struct net_device*,struct cas*,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t cas_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct cas *cp = netdev_priv(dev);
	unsigned long flags;
	u32 status = readl(cp->regs + REG_INTR_STATUS);

	if (status == 0)
		return IRQ_NONE;

	spin_lock_irqsave(&cp->lock, flags);
	if (status & (INTR_TX_ALL | INTR_TX_INTME)) {
		cas_tx(dev, cp, status);
		status &= ~(INTR_TX_ALL | INTR_TX_INTME);
	}

	if (status & INTR_RX_DONE) {
#ifdef USE_NAPI
		cas_mask_intr(cp);
		napi_schedule(&cp->napi);
#else
		cas_rx_ringN(cp, 0, 0);
#endif
		status &= ~INTR_RX_DONE;
	}

	if (status)
		cas_handle_irq(dev, cp, status);
	spin_unlock_irqrestore(&cp->lock, flags);
	return IRQ_HANDLED;
}