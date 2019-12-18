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
struct irq_domain {int dummy; } ;
struct irq_desc {int dummy; } ;
struct irq_chip_generic {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ICPU_CFG_INTR_DST_INTR_IDENT (int /*<<< orphan*/ ) ; 
 int __fls (int) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (struct irq_domain*,int) ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (struct irq_domain*,int /*<<< orphan*/ ) ; 
 int irq_reg_readl (struct irq_chip_generic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_irq_handler(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct irq_domain *d = irq_desc_get_handler_data(desc);
	struct irq_chip_generic *gc = irq_get_domain_generic_chip(d, 0);
	u32 reg = irq_reg_readl(gc, ICPU_CFG_INTR_DST_INTR_IDENT(0));

	chained_irq_enter(chip, desc);

	while (reg) {
		u32 hwirq = __fls(reg);

		generic_handle_irq(irq_find_mapping(d, hwirq));
		reg &= ~(BIT(hwirq));
	}

	chained_irq_exit(chip, desc);
}