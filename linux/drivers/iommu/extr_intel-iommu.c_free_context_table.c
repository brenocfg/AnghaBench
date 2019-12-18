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
struct intel_iommu {int /*<<< orphan*/  lock; struct context_entry* root_entry; } ;
struct context_entry {int dummy; } ;

/* Variables and functions */
 int ROOT_ENTRY_NR ; 
 int /*<<< orphan*/  free_pgtable_page (struct context_entry*) ; 
 struct context_entry* iommu_context_addr (struct intel_iommu*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_supported (struct intel_iommu*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_context_table(struct intel_iommu *iommu)
{
	int i;
	unsigned long flags;
	struct context_entry *context;

	spin_lock_irqsave(&iommu->lock, flags);
	if (!iommu->root_entry) {
		goto out;
	}
	for (i = 0; i < ROOT_ENTRY_NR; i++) {
		context = iommu_context_addr(iommu, i, 0, 0);
		if (context)
			free_pgtable_page(context);

		if (!sm_supported(iommu))
			continue;

		context = iommu_context_addr(iommu, i, 0x80, 0);
		if (context)
			free_pgtable_page(context);

	}
	free_pgtable_page(iommu->root_entry);
	iommu->root_entry = NULL;
out:
	spin_unlock_irqrestore(&iommu->lock, flags);
}