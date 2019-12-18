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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt {scalar_t__ hwrm_short_cmd_req_addr; int /*<<< orphan*/  hwrm_short_cmd_req_dma_addr; int /*<<< orphan*/  hwrm_max_ext_req_len; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_hwrm_short_cmd_req(struct bnxt *bp)
{
	struct pci_dev *pdev = bp->pdev;

	if (bp->hwrm_short_cmd_req_addr)
		return 0;

	bp->hwrm_short_cmd_req_addr =
		dma_alloc_coherent(&pdev->dev, bp->hwrm_max_ext_req_len,
				   &bp->hwrm_short_cmd_req_dma_addr,
				   GFP_KERNEL);
	if (!bp->hwrm_short_cmd_req_addr)
		return -ENOMEM;

	return 0;
}