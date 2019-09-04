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
struct lpc32xx_irq_chip {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_INTC_MASK ; 
 struct lpc32xx_irq_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int lpc32xx_ic_read (struct lpc32xx_irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_ic_write (struct lpc32xx_irq_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpc32xx_irq_mask(struct irq_data *d)
{
	struct lpc32xx_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 val, mask = BIT(d->hwirq);

	val = lpc32xx_ic_read(ic, LPC32XX_INTC_MASK) & ~mask;
	lpc32xx_ic_write(ic, LPC32XX_INTC_MASK, val);
}