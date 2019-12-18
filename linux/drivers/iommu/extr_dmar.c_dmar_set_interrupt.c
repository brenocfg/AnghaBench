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
struct intel_iommu {int irq; int /*<<< orphan*/  name; int /*<<< orphan*/  node; int /*<<< orphan*/  seq_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_NO_THREAD ; 
 int dmar_alloc_hwirq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct intel_iommu*) ; 
 int /*<<< orphan*/  dmar_fault ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct intel_iommu*) ; 

int dmar_set_interrupt(struct intel_iommu *iommu)
{
	int irq, ret;

	/*
	 * Check if the fault interrupt is already initialized.
	 */
	if (iommu->irq)
		return 0;

	irq = dmar_alloc_hwirq(iommu->seq_id, iommu->node, iommu);
	if (irq > 0) {
		iommu->irq = irq;
	} else {
		pr_err("No free IRQ vectors\n");
		return -EINVAL;
	}

	ret = request_irq(irq, dmar_fault, IRQF_NO_THREAD, iommu->name, iommu);
	if (ret)
		pr_err("Can't request irq\n");
	return ret;
}