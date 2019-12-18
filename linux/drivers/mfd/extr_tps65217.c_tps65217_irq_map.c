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
struct tps65217 {int /*<<< orphan*/  irq; } ;
struct irq_domain {struct tps65217* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct tps65217*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (unsigned int,int) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 
 int /*<<< orphan*/  irq_set_parent (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps65217_irq_chip ; 

__attribute__((used)) static int tps65217_irq_map(struct irq_domain *h, unsigned int virq,
			irq_hw_number_t hw)
{
	struct tps65217 *tps = h->host_data;

	irq_set_chip_data(virq, tps);
	irq_set_chip_and_handler(virq, &tps65217_irq_chip, handle_edge_irq);
	irq_set_nested_thread(virq, 1);
	irq_set_parent(virq, tps->irq);
	irq_set_noprobe(virq);

	return 0;
}