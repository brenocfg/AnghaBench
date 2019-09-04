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
struct irq_data {TYPE_1__* parent_data; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {scalar_t__ chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int irq_chip_set_affinity_parent (struct irq_data*,struct cpumask const*,int) ; 

__attribute__((used)) static int stm32_exti_h_set_affinity(struct irq_data *d,
				     const struct cpumask *dest, bool force)
{
	if (d->parent_data->chip)
		return irq_chip_set_affinity_parent(d, dest, force);

	return -EINVAL;
}