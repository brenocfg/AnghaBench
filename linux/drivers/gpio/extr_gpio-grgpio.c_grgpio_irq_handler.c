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
struct TYPE_4__ {int ngpio; int /*<<< orphan*/  bgpio_lock; } ;
struct grgpio_priv {int imask; int /*<<< orphan*/  dev; TYPE_2__ gc; TYPE_1__* uirqs; struct grgpio_lirq* lirqs; } ;
struct grgpio_lirq {size_t index; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int uirq; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t grgpio_irq_handler(int irq, void *dev)
{
	struct grgpio_priv *priv = dev;
	int ngpio = priv->gc.ngpio;
	unsigned long flags;
	int i;
	int match = 0;

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	/*
	 * For each gpio line, call its interrupt handler if it its underlying
	 * irq matches the current irq that is handled.
	 */
	for (i = 0; i < ngpio; i++) {
		struct grgpio_lirq *lirq = &priv->lirqs[i];

		if (priv->imask & BIT(i) && lirq->index >= 0 &&
		    priv->uirqs[lirq->index].uirq == irq) {
			generic_handle_irq(lirq->irq);
			match = 1;
		}
	}

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);

	if (!match)
		dev_warn(priv->dev, "No gpio line matched irq %d\n", irq);

	return IRQ_HANDLED;
}