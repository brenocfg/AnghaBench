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
struct irq_domain {struct grgpio_priv* host_data; } ;
struct grgpio_uirq {scalar_t__ refcnt; int /*<<< orphan*/  uirq; } ;
struct TYPE_2__ {int ngpio; int /*<<< orphan*/  bgpio_lock; } ;
struct grgpio_priv {TYPE_1__ gc; struct grgpio_uirq* uirqs; struct grgpio_lirq* lirqs; } ;
struct grgpio_lirq {unsigned int irq; int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct grgpio_priv*) ; 
 int /*<<< orphan*/  grgpio_set_imask (struct grgpio_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void grgpio_irq_unmap(struct irq_domain *d, unsigned int irq)
{
	struct grgpio_priv *priv = d->host_data;
	int index;
	struct grgpio_lirq *lirq;
	struct grgpio_uirq *uirq;
	unsigned long flags;
	int ngpio = priv->gc.ngpio;
	int i;

	irq_set_chip_and_handler(irq, NULL, NULL);
	irq_set_chip_data(irq, NULL);

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	/* Free underlying irq if last user unmapped */
	index = -1;
	for (i = 0; i < ngpio; i++) {
		lirq = &priv->lirqs[i];
		if (lirq->irq == irq) {
			grgpio_set_imask(priv, i, 0);
			lirq->irq = 0;
			index = lirq->index;
			break;
		}
	}
	WARN_ON(index < 0);

	if (index >= 0) {
		uirq = &priv->uirqs[lirq->index];
		uirq->refcnt--;
		if (uirq->refcnt == 0)
			free_irq(uirq->uirq, priv);
	}

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);
}