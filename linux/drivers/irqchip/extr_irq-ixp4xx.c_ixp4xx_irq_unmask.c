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
typedef  int /*<<< orphan*/  u32 ;
struct ixp4xx_irq {scalar_t__ irqbase; scalar_t__ is_356; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IXP4XX_ICMR ; 
 scalar_t__ IXP4XX_ICMR2 ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ixp4xx_irq* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void ixp4xx_irq_unmask(struct irq_data *d)
{
	struct ixp4xx_irq *ixi = irq_data_get_irq_chip_data(d);
	u32 val;

	if (ixi->is_356 && d->hwirq >= 32) {
		val = __raw_readl(ixi->irqbase + IXP4XX_ICMR2);
		val |= BIT(d->hwirq - 32);
		__raw_writel(val, ixi->irqbase + IXP4XX_ICMR2);
	} else {
		val = __raw_readl(ixi->irqbase + IXP4XX_ICMR);
		val |= BIT(d->hwirq);
		__raw_writel(val, ixi->irqbase + IXP4XX_ICMR);
	}
}