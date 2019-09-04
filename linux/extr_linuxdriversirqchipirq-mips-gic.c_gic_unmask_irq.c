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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 unsigned int GIC_HWIRQ_TO_SHARED (int /*<<< orphan*/ ) ; 
 unsigned int cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_clear_pcpu_masks (unsigned int) ; 
 int /*<<< orphan*/  irq_data_get_effective_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  pcpu_masks ; 
 int /*<<< orphan*/  per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_gic_smask (unsigned int) ; 

__attribute__((used)) static void gic_unmask_irq(struct irq_data *d)
{
	unsigned int intr = GIC_HWIRQ_TO_SHARED(d->hwirq);
	unsigned int cpu;

	write_gic_smask(intr);

	gic_clear_pcpu_masks(intr);
	cpu = cpumask_first(irq_data_get_effective_affinity_mask(d));
	set_bit(intr, per_cpu_ptr(pcpu_masks, cpu));
}