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
struct ipu_soc {int /*<<< orphan*/  domain; int /*<<< orphan*/  irq_sync; int /*<<< orphan*/  irq_err; } ;

/* Variables and functions */
 int IPU_NUM_IRQS ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipu_irq_exit(struct ipu_soc *ipu)
{
	int i, irq;

	irq_set_chained_handler_and_data(ipu->irq_err, NULL, NULL);
	irq_set_chained_handler_and_data(ipu->irq_sync, NULL, NULL);

	/* TODO: remove irq_domain_generic_chips */

	for (i = 0; i < IPU_NUM_IRQS; i++) {
		irq = irq_linear_revmap(ipu->domain, i);
		if (irq)
			irq_dispose_mapping(irq);
	}

	irq_domain_remove(ipu->domain);
}