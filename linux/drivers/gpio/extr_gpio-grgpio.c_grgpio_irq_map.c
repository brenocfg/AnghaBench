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
struct TYPE_2__ {int /*<<< orphan*/  bgpio_lock; } ;
struct grgpio_priv {TYPE_1__ gc; int /*<<< orphan*/  dev; struct grgpio_uirq* uirqs; struct grgpio_lirq* lirqs; } ;
struct grgpio_lirq {size_t index; unsigned int irq; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grgpio_irq_chip ; 
 int /*<<< orphan*/  grgpio_irq_handler ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct grgpio_priv*) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct grgpio_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grgpio_irq_map(struct irq_domain *d, unsigned int irq,
			  irq_hw_number_t hwirq)
{
	struct grgpio_priv *priv = d->host_data;
	struct grgpio_lirq *lirq;
	struct grgpio_uirq *uirq;
	unsigned long flags;
	int offset = hwirq;
	int ret = 0;

	if (!priv)
		return -EINVAL;

	lirq = &priv->lirqs[offset];
	if (lirq->index < 0)
		return -EINVAL;

	dev_dbg(priv->dev, "Mapping irq %d for gpio line %d\n",
		irq, offset);

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	/* Request underlying irq if not already requested */
	lirq->irq = irq;
	uirq = &priv->uirqs[lirq->index];
	if (uirq->refcnt == 0) {
		ret = request_irq(uirq->uirq, grgpio_irq_handler, 0,
				  dev_name(priv->dev), priv);
		if (ret) {
			dev_err(priv->dev,
				"Could not request underlying irq %d\n",
				uirq->uirq);

			spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);

			return ret;
		}
	}
	uirq->refcnt++;

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);

	/* Setup irq  */
	irq_set_chip_data(irq, priv);
	irq_set_chip_and_handler(irq, &grgpio_irq_chip,
				 handle_simple_irq);
	irq_set_noprobe(irq);

	return ret;
}