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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ FIRST_EXT_IRQ ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_domain* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (struct irq_domain*,scalar_t__) ; 
 scalar_t__ irqd_to_hwirq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idu_cascade_isr(struct irq_desc *desc)
{
	struct irq_domain *idu_domain = irq_desc_get_handler_data(desc);
	struct irq_chip *core_chip = irq_desc_get_chip(desc);
	irq_hw_number_t core_hwirq = irqd_to_hwirq(irq_desc_get_irq_data(desc));
	irq_hw_number_t idu_hwirq = core_hwirq - FIRST_EXT_IRQ;

	chained_irq_enter(core_chip, desc);
	generic_handle_irq(irq_find_mapping(idu_domain, idu_hwirq));
	chained_irq_exit(core_chip, desc);
}