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
struct mvebu_pic {int /*<<< orphan*/  irq_chip; } ;
struct irq_domain {struct mvebu_pic* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  handle_percpu_devid_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct mvebu_pic*) ; 
 int /*<<< orphan*/  irq_set_percpu_devid (unsigned int) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvebu_pic_irq_map(struct irq_domain *domain, unsigned int virq,
			     irq_hw_number_t hwirq)
{
	struct mvebu_pic *pic = domain->host_data;

	irq_set_percpu_devid(virq);
	irq_set_chip_data(virq, pic);
	irq_set_chip_and_handler(virq, &pic->irq_chip,
				 handle_percpu_devid_irq);
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_probe(virq);

	return 0;
}