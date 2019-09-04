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
struct irq_data {int /*<<< orphan*/  mask; } ;
struct irq_chip_generic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_AIC_ISCR ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_reg_writel (struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aic_retrigger(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	/* Enable interrupt on AIC5 */
	irq_gc_lock(gc);
	irq_reg_writel(gc, d->mask, AT91_AIC_ISCR);
	irq_gc_unlock(gc);

	return 0;
}