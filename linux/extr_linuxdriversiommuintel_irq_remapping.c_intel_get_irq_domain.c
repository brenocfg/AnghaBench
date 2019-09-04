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
struct irq_domain {int dummy; } ;
struct irq_alloc_info {int type; int /*<<< orphan*/  msi_dev; } ;
struct intel_iommu {struct irq_domain* ir_msi_domain; } ;

/* Variables and functions */
#define  X86_IRQ_ALLOC_TYPE_MSI 129 
#define  X86_IRQ_ALLOC_TYPE_MSIX 128 
 struct intel_iommu* map_dev_to_ir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct irq_domain *intel_get_irq_domain(struct irq_alloc_info *info)
{
	struct intel_iommu *iommu;

	if (!info)
		return NULL;

	switch (info->type) {
	case X86_IRQ_ALLOC_TYPE_MSI:
	case X86_IRQ_ALLOC_TYPE_MSIX:
		iommu = map_dev_to_ir(info->msi_dev);
		if (iommu)
			return iommu->ir_msi_domain;
		break;
	default:
		break;
	}

	return NULL;
}