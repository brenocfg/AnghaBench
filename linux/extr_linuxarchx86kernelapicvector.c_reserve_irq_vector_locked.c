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
struct apic_chip_data {int can_reserve; int has_reserved; } ;

/* Variables and functions */
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_matrix_reserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_set_can_reserve (struct irq_data*) ; 
 int /*<<< orphan*/  trace_vector_reserve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_assign_managed_shutdown (struct irq_data*) ; 
 int /*<<< orphan*/  vector_matrix ; 

__attribute__((used)) static void reserve_irq_vector_locked(struct irq_data *irqd)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);

	irq_matrix_reserve(vector_matrix);
	apicd->can_reserve = true;
	apicd->has_reserved = true;
	irqd_set_can_reserve(irqd);
	trace_vector_reserve(irqd->irq, 0);
	vector_assign_managed_shutdown(irqd);
}