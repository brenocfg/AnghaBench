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
struct irq_domain {int /*<<< orphan*/  host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  imx_irqsteer_irq_chip ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_irqsteer_irq_map(struct irq_domain *h, unsigned int irq,
				irq_hw_number_t hwirq)
{
	irq_set_status_flags(irq, IRQ_LEVEL);
	irq_set_chip_data(irq, h->host_data);
	irq_set_chip_and_handler(irq, &imx_irqsteer_irq_chip, handle_level_irq);

	return 0;
}