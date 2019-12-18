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
struct irq_domain {int revmap_size; } ;
struct irq_desc {int dummy; } ;
struct irq_chip_generic {scalar_t__ irq_base; scalar_t__ reg_base; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ APB_INT_FINALSTATUS_L ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_find_mapping (struct irq_domain*,scalar_t__) ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (struct irq_domain*,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void dw_apb_ictl_handler(struct irq_desc *desc)
{
	struct irq_domain *d = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	int n;

	chained_irq_enter(chip, desc);

	for (n = 0; n < d->revmap_size; n += 32) {
		struct irq_chip_generic *gc = irq_get_domain_generic_chip(d, n);
		u32 stat = readl_relaxed(gc->reg_base + APB_INT_FINALSTATUS_L);

		while (stat) {
			u32 hwirq = ffs(stat) - 1;
			u32 virq = irq_find_mapping(d, gc->irq_base + hwirq);

			generic_handle_irq(virq);
			stat &= ~(1 << hwirq);
		}
	}

	chained_irq_exit(chip, desc);
}