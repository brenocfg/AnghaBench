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
struct TYPE_2__ {int nr_regs; unsigned int irq; scalar_t__ base_irq; int /*<<< orphan*/ ** priority_mask; int /*<<< orphan*/ ** saved_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_free_descs (scalar_t__,int) ; 
 int /*<<< orphan*/  irq_remove_generic_chip (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/ ** prcm_irq_chips ; 
 TYPE_1__* prcm_irq_setup ; 

void omap_prcm_irq_cleanup(void)
{
	unsigned int irq;
	int i;

	if (!prcm_irq_setup) {
		pr_err("PRCM: IRQ handler not initialized; cannot cleanup\n");
		return;
	}

	if (prcm_irq_chips) {
		for (i = 0; i < prcm_irq_setup->nr_regs; i++) {
			if (prcm_irq_chips[i])
				irq_remove_generic_chip(prcm_irq_chips[i],
					0xffffffff, 0, 0);
			prcm_irq_chips[i] = NULL;
		}
		kfree(prcm_irq_chips);
		prcm_irq_chips = NULL;
	}

	kfree(prcm_irq_setup->saved_mask);
	prcm_irq_setup->saved_mask = NULL;

	kfree(prcm_irq_setup->priority_mask);
	prcm_irq_setup->priority_mask = NULL;

	irq = prcm_irq_setup->irq;
	irq_set_chained_handler(irq, NULL);

	if (prcm_irq_setup->base_irq > 0)
		irq_free_descs(prcm_irq_setup->base_irq,
			prcm_irq_setup->nr_regs * 32);
	prcm_irq_setup->base_irq = 0;
}