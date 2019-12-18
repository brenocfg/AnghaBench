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
struct irq_chip_generic {int mask_cache; scalar_t__ irq_base; scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ ORION_BRIDGE_IRQ_CAUSE ; 
 int __fls (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (struct irq_domain*,scalar_t__) ; 
 struct irq_chip_generic* irq_get_domain_generic_chip (struct irq_domain*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void orion_bridge_irq_handler(struct irq_desc *desc)
{
	struct irq_domain *d = irq_desc_get_handler_data(desc);

	struct irq_chip_generic *gc = irq_get_domain_generic_chip(d, 0);
	u32 stat = readl_relaxed(gc->reg_base + ORION_BRIDGE_IRQ_CAUSE) &
		   gc->mask_cache;

	while (stat) {
		u32 hwirq = __fls(stat);

		generic_handle_irq(irq_find_mapping(d, gc->irq_base + hwirq));
		stat &= ~(1 << hwirq);
	}
}