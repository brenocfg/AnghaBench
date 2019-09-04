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
struct pnv_phb {scalar_t__ type; int /*<<< orphan*/  opal_id; } ;
struct pnv_ioda_pe {int /*<<< orphan*/  pe_number; TYPE_1__* pdev; struct pnv_phb* phb; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OPAL_SUCCESS ; 
 scalar_t__ PNV_PHB_NPU_NVLINK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memblock_end_of_DRAM () ; 
 scalar_t__ opal_pci_map_pe_dma_window_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pnv_npu_unset_window (struct pnv_ioda_pe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_tce_invalidate_entire (struct pnv_phb*,int) ; 
 int /*<<< orphan*/  roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnv_npu_dma_set_bypass(struct pnv_ioda_pe *npe)
{
	struct pnv_phb *phb = npe->phb;
	int64_t rc = 0;
	phys_addr_t top = memblock_end_of_DRAM();

	if (phb->type != PNV_PHB_NPU_NVLINK || !npe->pdev)
		return -EINVAL;

	rc = pnv_npu_unset_window(npe, 0);
	if (rc != OPAL_SUCCESS)
		return rc;

	/* Enable the bypass window */

	top = roundup_pow_of_two(top);
	dev_info(&npe->pdev->dev, "Enabling bypass for PE %x\n",
			npe->pe_number);
	rc = opal_pci_map_pe_dma_window_real(phb->opal_id,
			npe->pe_number, npe->pe_number,
			0 /* bypass base */, top);

	if (rc == OPAL_SUCCESS)
		pnv_pci_ioda2_tce_invalidate_entire(phb, false);

	return rc;
}