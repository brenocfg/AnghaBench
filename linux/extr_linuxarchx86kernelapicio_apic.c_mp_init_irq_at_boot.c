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

/* Variables and functions */
 scalar_t__ mp_is_legacy_irq (int) ; 
 int /*<<< orphan*/  nr_legacy_irqs () ; 

__attribute__((used)) static inline int mp_init_irq_at_boot(int ioapic, int irq)
{
	if (!nr_legacy_irqs())
		return 0;

	return ioapic == 0 || mp_is_legacy_irq(irq);
}