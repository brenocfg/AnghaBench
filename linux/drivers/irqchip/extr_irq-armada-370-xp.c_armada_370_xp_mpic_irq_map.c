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
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ ARMADA_370_XP_INT_CLEAR_MASK_OFFS ; 
 scalar_t__ ARMADA_370_XP_INT_SET_ENABLE_OFFS ; 
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  armada_370_xp_irq_chip ; 
 int /*<<< orphan*/  armada_370_xp_irq_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  handle_percpu_devid_irq ; 
 int /*<<< orphan*/  irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_percpu_devid (unsigned int) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  irqd_set_single_target (int /*<<< orphan*/ ) ; 
 scalar_t__ is_percpu_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ main_int_base ; 
 scalar_t__ per_cpu_int_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int armada_370_xp_mpic_irq_map(struct irq_domain *h,
				      unsigned int virq, irq_hw_number_t hw)
{
	armada_370_xp_irq_mask(irq_get_irq_data(virq));
	if (!is_percpu_irq(hw))
		writel(hw, per_cpu_int_base +
			ARMADA_370_XP_INT_CLEAR_MASK_OFFS);
	else
		writel(hw, main_int_base + ARMADA_370_XP_INT_SET_ENABLE_OFFS);
	irq_set_status_flags(virq, IRQ_LEVEL);

	if (is_percpu_irq(hw)) {
		irq_set_percpu_devid(virq);
		irq_set_chip_and_handler(virq, &armada_370_xp_irq_chip,
					handle_percpu_devid_irq);
	} else {
		irq_set_chip_and_handler(virq, &armada_370_xp_irq_chip,
					handle_level_irq);
		irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(virq)));
	}
	irq_set_probe(virq);

	return 0;
}