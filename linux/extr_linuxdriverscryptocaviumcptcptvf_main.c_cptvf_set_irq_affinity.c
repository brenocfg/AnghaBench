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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {int vfid; int /*<<< orphan*/ * affinity_mask; int /*<<< orphan*/  node; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpumask_local_spread (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cptvf_set_irq_affinity(struct cpt_vf *cptvf, int vec)
{
	struct pci_dev *pdev = cptvf->pdev;
	int cpu;

	if (!zalloc_cpumask_var(&cptvf->affinity_mask[vec],
				GFP_KERNEL)) {
		dev_err(&pdev->dev, "Allocation failed for affinity_mask for VF %d",
			cptvf->vfid);
		return;
	}

	cpu = cptvf->vfid % num_online_cpus();
	cpumask_set_cpu(cpumask_local_spread(cpu, cptvf->node),
			cptvf->affinity_mask[vec]);
	irq_set_affinity_hint(pci_irq_vector(pdev, vec),
			cptvf->affinity_mask[vec]);
}