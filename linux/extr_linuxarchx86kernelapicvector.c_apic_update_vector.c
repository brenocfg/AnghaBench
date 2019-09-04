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
struct irq_desc {int dummy; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct apic_chip_data {unsigned int vector; unsigned int cpu; unsigned int prev_vector; int move_in_progress; unsigned int prev_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct irq_desc*) ; 
 unsigned int MANAGED_IRQ_SHUTDOWN_VECTOR ; 
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 scalar_t__ cpu_online (unsigned int) ; 
 struct irq_desc* irq_data_to_desc (struct irq_data*) ; 
 int /*<<< orphan*/  irq_matrix_free (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int irqd_affinity_is_managed (struct irq_data*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct irq_desc** per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_vector_update (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vector_irq ; 
 int /*<<< orphan*/  vector_lock ; 
 int /*<<< orphan*/  vector_matrix ; 

__attribute__((used)) static void apic_update_vector(struct irq_data *irqd, unsigned int newvec,
			       unsigned int newcpu)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);
	struct irq_desc *desc = irq_data_to_desc(irqd);
	bool managed = irqd_affinity_is_managed(irqd);

	lockdep_assert_held(&vector_lock);

	trace_vector_update(irqd->irq, newvec, newcpu, apicd->vector,
			    apicd->cpu);

	/*
	 * If there is no vector associated or if the associated vector is
	 * the shutdown vector, which is associated to make PCI/MSI
	 * shutdown mode work, then there is nothing to release. Clear out
	 * prev_vector for this and the offlined target case.
	 */
	apicd->prev_vector = 0;
	if (!apicd->vector || apicd->vector == MANAGED_IRQ_SHUTDOWN_VECTOR)
		goto setnew;
	/*
	 * If the target CPU of the previous vector is online, then mark
	 * the vector as move in progress and store it for cleanup when the
	 * first interrupt on the new vector arrives. If the target CPU is
	 * offline then the regular release mechanism via the cleanup
	 * vector is not possible and the vector can be immediately freed
	 * in the underlying matrix allocator.
	 */
	if (cpu_online(apicd->cpu)) {
		apicd->move_in_progress = true;
		apicd->prev_vector = apicd->vector;
		apicd->prev_cpu = apicd->cpu;
	} else {
		irq_matrix_free(vector_matrix, apicd->cpu, apicd->vector,
				managed);
	}

setnew:
	apicd->vector = newvec;
	apicd->cpu = newcpu;
	BUG_ON(!IS_ERR_OR_NULL(per_cpu(vector_irq, newcpu)[newvec]));
	per_cpu(vector_irq, newcpu)[newvec] = desc;
}