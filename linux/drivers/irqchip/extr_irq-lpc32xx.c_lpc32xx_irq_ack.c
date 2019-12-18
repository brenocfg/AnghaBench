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
struct lpc32xx_irq_chip {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XX_INTC_RAW ; 
 struct lpc32xx_irq_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lpc32xx_ic_write (struct lpc32xx_irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_irq_ack(struct irq_data *d)
{
	struct lpc32xx_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 mask = BIT(d->hwirq);

	lpc32xx_ic_write(ic, LPC32XX_INTC_RAW, mask);
}