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
struct irq_domain {int dummy; } ;
struct irq_data {int hwirq; int /*<<< orphan*/  mask; struct irq_domain* domain; } ;
struct irq_chip_generic {int /*<<< orphan*/  mask_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_AIC5_IECR ; 
 int /*<<< orphan*/  AT91_AIC5_SSR ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (struct irq_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_reg_writel (struct irq_chip_generic*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aic5_unmask(struct irq_data *d)
{
	struct irq_domain *domain = d->domain;
	struct irq_chip_generic *bgc = irq_get_domain_generic_chip(domain, 0);
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);

	/*
	 * Enable interrupt on AIC5. We always take the lock of the
	 * first irq chip as all chips share the same registers.
	 */
	irq_gc_lock(bgc);
	irq_reg_writel(gc, d->hwirq, AT91_AIC5_SSR);
	irq_reg_writel(gc, 1, AT91_AIC5_IECR);
	gc->mask_cache |= d->mask;
	irq_gc_unlock(bgc);
}