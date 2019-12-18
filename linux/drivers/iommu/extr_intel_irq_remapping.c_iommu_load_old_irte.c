#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct irte {int dummy; } ;
struct intel_iommu {TYPE_1__* ir_table; scalar_t__ reg; } ;
typedef  int phys_addr_t ;
struct TYPE_5__ {scalar_t__ present; } ;
struct TYPE_4__ {int /*<<< orphan*/  bitmap; TYPE_2__* base; } ;

/* Variables and functions */
 scalar_t__ DMAR_IRTA_REG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int INTR_REMAP_TABLE_ENTRIES ; 
 int INTR_REMAP_TABLE_REG_SIZE ; 
 int INTR_REMAP_TABLE_REG_SIZE_MASK ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 int VTD_PAGE_MASK ; 
 int /*<<< orphan*/  __iommu_flush_cache (struct intel_iommu*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned int,int) ; 
 int dmar_readq (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct irte*,size_t) ; 
 struct irte* memremap (int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (struct irte*) ; 

__attribute__((used)) static int iommu_load_old_irte(struct intel_iommu *iommu)
{
	struct irte *old_ir_table;
	phys_addr_t irt_phys;
	unsigned int i;
	size_t size;
	u64 irta;

	/* Check whether the old ir-table has the same size as ours */
	irta = dmar_readq(iommu->reg + DMAR_IRTA_REG);
	if ((irta & INTR_REMAP_TABLE_REG_SIZE_MASK)
	     != INTR_REMAP_TABLE_REG_SIZE)
		return -EINVAL;

	irt_phys = irta & VTD_PAGE_MASK;
	size     = INTR_REMAP_TABLE_ENTRIES*sizeof(struct irte);

	/* Map the old IR table */
	old_ir_table = memremap(irt_phys, size, MEMREMAP_WB);
	if (!old_ir_table)
		return -ENOMEM;

	/* Copy data over */
	memcpy(iommu->ir_table->base, old_ir_table, size);

	__iommu_flush_cache(iommu, iommu->ir_table->base, size);

	/*
	 * Now check the table for used entries and mark those as
	 * allocated in the bitmap
	 */
	for (i = 0; i < INTR_REMAP_TABLE_ENTRIES; i++) {
		if (iommu->ir_table->base[i].present)
			bitmap_set(iommu->ir_table->bitmap, i, 1);
	}

	memunmap(old_ir_table);

	return 0;
}