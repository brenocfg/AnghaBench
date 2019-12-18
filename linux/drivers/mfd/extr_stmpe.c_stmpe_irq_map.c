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
struct stmpe {TYPE_1__* variant; } ;
struct irq_domain {struct stmpe* host_data; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {scalar_t__ id_val; } ;

/* Variables and functions */
 scalar_t__ STMPE801_ID ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct stmpe*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (unsigned int,int) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 
 struct irq_chip stmpe_irq_chip ; 

__attribute__((used)) static int stmpe_irq_map(struct irq_domain *d, unsigned int virq,
                                irq_hw_number_t hwirq)
{
	struct stmpe *stmpe = d->host_data;
	struct irq_chip *chip = NULL;

	if (stmpe->variant->id_val != STMPE801_ID)
		chip = &stmpe_irq_chip;

	irq_set_chip_data(virq, stmpe);
	irq_set_chip_and_handler(virq, chip, handle_edge_irq);
	irq_set_nested_thread(virq, 1);
	irq_set_noprobe(virq);

	return 0;
}