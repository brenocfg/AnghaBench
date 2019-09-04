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
struct irq_data {int dummy; } ;
struct bcm6345_l1_chip {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 unsigned int cpumask_first_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_affinity_mask (struct irq_data*) ; 

__attribute__((used)) static inline unsigned int cpu_for_irq(struct bcm6345_l1_chip *intc,
					struct irq_data *d)
{
	return cpumask_first_and(&intc->cpumask, irq_data_get_affinity_mask(d));
}