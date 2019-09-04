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
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct TYPE_2__ {scalar_t__* tables; } ;
struct pnv_ioda_pe {struct pnv_phb* phb; int /*<<< orphan*/  pe_number; TYPE_1__ table_group; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ opal_pci_map_pe_dma_window_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_err (struct pnv_ioda_pe*,char*,scalar_t__) ; 
 int /*<<< orphan*/  pnv_npu_unset_window (struct pnv_ioda_pe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_tce_invalidate_entire (struct pnv_phb*,int) ; 

void pnv_npu_take_ownership(struct pnv_ioda_pe *npe)
{
	struct pnv_phb *phb = npe->phb;
	int64_t rc;

	/*
	 * Note: NPU has just a single TVE in the hardware which means that
	 * while used by the kernel, it can have either 32bit window or
	 * DMA bypass but never both. So we deconfigure 32bit window only
	 * if it was enabled at the moment of ownership change.
	 */
	if (npe->table_group.tables[0]) {
		pnv_npu_unset_window(npe, 0);
		return;
	}

	/* Disable bypass */
	rc = opal_pci_map_pe_dma_window_real(phb->opal_id,
			npe->pe_number, npe->pe_number,
			0 /* bypass base */, 0);
	if (rc) {
		pe_err(npe, "Failed to disable bypass, err %lld\n", rc);
		return;
	}
	pnv_pci_ioda2_tce_invalidate_entire(npe->phb, false);
}