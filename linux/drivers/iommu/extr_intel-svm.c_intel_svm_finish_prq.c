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
struct intel_iommu {int /*<<< orphan*/ * prq; scalar_t__ pr_irq; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ DMAR_PQA_REG ; 
 scalar_t__ DMAR_PQH_REG ; 
 scalar_t__ DMAR_PQT_REG ; 
 int /*<<< orphan*/  PRQ_ORDER ; 
 int /*<<< orphan*/  dmar_free_hwirq (scalar_t__) ; 
 int /*<<< orphan*/  dmar_writeq (scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct intel_iommu*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 

int intel_svm_finish_prq(struct intel_iommu *iommu)
{
	dmar_writeq(iommu->reg + DMAR_PQH_REG, 0ULL);
	dmar_writeq(iommu->reg + DMAR_PQT_REG, 0ULL);
	dmar_writeq(iommu->reg + DMAR_PQA_REG, 0ULL);

	if (iommu->pr_irq) {
		free_irq(iommu->pr_irq, iommu);
		dmar_free_hwirq(iommu->pr_irq);
		iommu->pr_irq = 0;
	}

	free_pages((unsigned long)iommu->prq, PRQ_ORDER);
	iommu->prq = NULL;

	return 0;
}