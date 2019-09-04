#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * tables; } ;
struct pnv_ioda_pe {int flags; TYPE_1__* pdev; TYPE_2__ table_group; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PNV_IODA_PE_DEV ; 
 int /*<<< orphan*/  dma_npu_ops ; 
 struct pnv_ioda_pe* get_gpu_pci_dev_and_pe (struct pnv_ioda_pe*,struct pci_dev**) ; 
 int /*<<< orphan*/  pnv_npu_set_window (struct pnv_ioda_pe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pnv_npu_dma_set_32(struct pnv_ioda_pe *npe)
{
	struct pci_dev *gpdev;
	struct pnv_ioda_pe *gpe;
	int64_t rc;

	/*
	 * Find the assoicated PCI devices and get the dma window
	 * information from there.
	 */
	if (!npe->pdev || !(npe->flags & PNV_IODA_PE_DEV))
		return;

	gpe = get_gpu_pci_dev_and_pe(npe, &gpdev);
	if (!gpe)
		return;

	rc = pnv_npu_set_window(npe, 0, gpe->table_group.tables[0]);

	/*
	 * We don't initialise npu_pe->tce32_table as we always use
	 * dma_npu_ops which are nops.
	 */
	set_dma_ops(&npe->pdev->dev, &dma_npu_ops);
}