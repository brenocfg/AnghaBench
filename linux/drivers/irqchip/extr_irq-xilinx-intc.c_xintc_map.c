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
struct irq_domain {int dummy; } ;
typedef  int irq_hw_number_t ;
struct TYPE_2__ {int intr_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  intc_dev ; 
 int /*<<< orphan*/  irq_clear_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* xintc_irqc ; 

__attribute__((used)) static int xintc_map(struct irq_domain *d, unsigned int irq, irq_hw_number_t hw)
{
	if (xintc_irqc->intr_mask & (1 << hw)) {
		irq_set_chip_and_handler_name(irq, &intc_dev,
						handle_edge_irq, "edge");
		irq_clear_status_flags(irq, IRQ_LEVEL);
	} else {
		irq_set_chip_and_handler_name(irq, &intc_dev,
						handle_level_irq, "level");
		irq_set_status_flags(irq, IRQ_LEVEL);
	}
	return 0;
}