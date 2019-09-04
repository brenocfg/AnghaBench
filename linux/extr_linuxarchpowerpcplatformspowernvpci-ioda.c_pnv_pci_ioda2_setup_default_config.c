#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_9__ {scalar_t__ tce32_size; } ;
struct pnv_ioda_pe {int flags; TYPE_3__* pdev; TYPE_4__ table_group; TYPE_2__* phb; } ;
struct iommu_table {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_1__* hose; } ;
struct TYPE_6__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_PAGE_SHIFT_4K ; 
 int PNV_IODA_PE_DEV ; 
 int /*<<< orphan*/  POWERNV_IOMMU_DEFAULT_LEVELS ; 
 int /*<<< orphan*/  __rounddown_pow_of_two (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_init_table (struct iommu_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_tce_table_put (struct iommu_table*) ; 
 int /*<<< orphan*/  memory_hotplug_max () ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pe_err (struct pnv_ioda_pe*,char*,long) ; 
 int /*<<< orphan*/  pnv_iommu_bypass_disabled ; 
 long pnv_pci_ioda2_create_table (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int,struct iommu_table**) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_set_bypass (struct pnv_ioda_pe*,int) ; 
 long pnv_pci_ioda2_set_window (TYPE_4__*,int /*<<< orphan*/ ,struct iommu_table*) ; 
 int /*<<< orphan*/  set_iommu_table_base (int /*<<< orphan*/ *,struct iommu_table*) ; 

__attribute__((used)) static long pnv_pci_ioda2_setup_default_config(struct pnv_ioda_pe *pe)
{
	struct iommu_table *tbl = NULL;
	long rc;

	/*
	 * crashkernel= specifies the kdump kernel's maximum memory at
	 * some offset and there is no guaranteed the result is a power
	 * of 2, which will cause errors later.
	 */
	const u64 max_memory = __rounddown_pow_of_two(memory_hotplug_max());

	/*
	 * In memory constrained environments, e.g. kdump kernel, the
	 * DMA window can be larger than available memory, which will
	 * cause errors later.
	 */
	const u64 window_size = min((u64)pe->table_group.tce32_size, max_memory);

	rc = pnv_pci_ioda2_create_table(&pe->table_group, 0,
			IOMMU_PAGE_SHIFT_4K,
			window_size,
			POWERNV_IOMMU_DEFAULT_LEVELS, false, &tbl);
	if (rc) {
		pe_err(pe, "Failed to create 32-bit TCE table, err %ld",
				rc);
		return rc;
	}

	iommu_init_table(tbl, pe->phb->hose->node);

	rc = pnv_pci_ioda2_set_window(&pe->table_group, 0, tbl);
	if (rc) {
		pe_err(pe, "Failed to configure 32-bit TCE table, err %ld\n",
				rc);
		iommu_tce_table_put(tbl);
		return rc;
	}

	if (!pnv_iommu_bypass_disabled)
		pnv_pci_ioda2_set_bypass(pe, true);

	/*
	 * Setting table base here only for carrying iommu_group
	 * further down to let iommu_add_device() do the job.
	 * pnv_pci_ioda_dma_dev_setup will override it later anyway.
	 */
	if (pe->flags & PNV_IODA_PE_DEV)
		set_iommu_table_base(&pe->pdev->dev, tbl);

	return 0;
}