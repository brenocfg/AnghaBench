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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct cpumask {int dummy; } ;
struct apic_chip_data {scalar_t__ is_managed; scalar_t__ has_reserved; } ;

/* Variables and functions */
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  irq_matrix_remove_managed (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  irq_matrix_remove_reserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_vector_teardown (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vector_matrix ; 

__attribute__((used)) static void vector_free_reserved_and_managed(struct irq_data *irqd)
{
	const struct cpumask *dest = irq_data_get_affinity_mask(irqd);
	struct apic_chip_data *apicd = apic_chip_data(irqd);

	trace_vector_teardown(irqd->irq, apicd->is_managed,
			      apicd->has_reserved);

	if (apicd->has_reserved)
		irq_matrix_remove_reserved(vector_matrix);
	if (apicd->is_managed)
		irq_matrix_remove_managed(vector_matrix, dest);
}