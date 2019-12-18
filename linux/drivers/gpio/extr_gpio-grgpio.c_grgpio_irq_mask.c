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
struct irq_data {int hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  bgpio_lock; } ;
struct grgpio_priv {TYPE_1__ gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  grgpio_set_imask (struct grgpio_priv*,int,int /*<<< orphan*/ ) ; 
 struct grgpio_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void grgpio_irq_mask(struct irq_data *d)
{
	struct grgpio_priv *priv = irq_data_get_irq_chip_data(d);
	int offset = d->hwirq;
	unsigned long flags;

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	grgpio_set_imask(priv, offset, 0);

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);
}