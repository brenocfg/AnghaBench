#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct irq_domain {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_3__ {int /*<<< orphan*/  irqchip; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,TYPE_1__*) ; 
 TYPE_1__ opal_event_irqchip ; 

__attribute__((used)) static int opal_event_map(struct irq_domain *d, unsigned int irq,
			irq_hw_number_t hwirq)
{
	irq_set_chip_data(irq, &opal_event_irqchip);
	irq_set_chip_and_handler(irq, &opal_event_irqchip.irqchip,
				handle_level_irq);

	return 0;
}