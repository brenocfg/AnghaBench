#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_iommu {TYPE_1__* ir_table; int /*<<< orphan*/ * ir_domain; int /*<<< orphan*/ * ir_msi_domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_REMAP_PAGE_ORDER ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void intel_teardown_irq_remapping(struct intel_iommu *iommu)
{
	if (iommu && iommu->ir_table) {
		if (iommu->ir_msi_domain) {
			irq_domain_remove(iommu->ir_msi_domain);
			iommu->ir_msi_domain = NULL;
		}
		if (iommu->ir_domain) {
			irq_domain_remove(iommu->ir_domain);
			iommu->ir_domain = NULL;
		}
		free_pages((unsigned long)iommu->ir_table->base,
			   INTR_REMAP_PAGE_ORDER);
		bitmap_free(iommu->ir_table->bitmap);
		kfree(iommu->ir_table);
		iommu->ir_table = NULL;
	}
}