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
struct nicvf {int num_vec; int /*<<< orphan*/ * affinity_mask; int /*<<< orphan*/  pdev; int /*<<< orphan*/  node; int /*<<< orphan*/ * irq_allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NICVF_INTR_ID_SQ ; 
 int /*<<< orphan*/  cpumask_local_spread (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nicvf_netdev_qidx (struct nicvf*,int) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nicvf_set_irq_affinity(struct nicvf *nic)
{
	int vec, cpu;

	for (vec = 0; vec < nic->num_vec; vec++) {
		if (!nic->irq_allocated[vec])
			continue;

		if (!zalloc_cpumask_var(&nic->affinity_mask[vec], GFP_KERNEL))
			return;
		 /* CQ interrupts */
		if (vec < NICVF_INTR_ID_SQ)
			/* Leave CPU0 for RBDR and other interrupts */
			cpu = nicvf_netdev_qidx(nic, vec) + 1;
		else
			cpu = 0;

		cpumask_set_cpu(cpumask_local_spread(cpu, nic->node),
				nic->affinity_mask[vec]);
		irq_set_affinity_hint(pci_irq_vector(nic->pdev, vec),
				      nic->affinity_mask[vec]);
	}
}