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
struct irq_alloc_info {scalar_t__ mask; } ;

/* Variables and functions */
 int assign_irq_vector (struct irq_data*,scalar_t__) ; 
 scalar_t__ irqd_affinity_is_managed (struct irq_data*) ; 
 int reserve_irq_vector (struct irq_data*) ; 
 int reserve_managed_vector (struct irq_data*) ; 

__attribute__((used)) static int
assign_irq_vector_policy(struct irq_data *irqd, struct irq_alloc_info *info)
{
	if (irqd_affinity_is_managed(irqd))
		return reserve_managed_vector(irqd);
	if (info->mask)
		return assign_irq_vector(irqd, info->mask);
	/*
	 * Make only a global reservation with no guarantee. A real vector
	 * is associated at activation time.
	 */
	return reserve_irq_vector(irqd);
}