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
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ ARMADA_370_XP_MAX_PER_CPU_IRQS ; 

__attribute__((used)) static inline bool is_percpu_irq(irq_hw_number_t irq)
{
	if (irq <= ARMADA_370_XP_MAX_PER_CPU_IRQS)
		return true;

	return false;
}