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
struct bnxt {int /*<<< orphan*/  hwrm_cmd_resp_addr; int /*<<< orphan*/  hwrm_cmd_resp_dma_addr; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_hwrm_resources(struct bnxt *bp)
{
	struct pci_dev *pdev = bp->pdev;

	bp->hwrm_cmd_resp_addr = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
						   &bp->hwrm_cmd_resp_dma_addr,
						   GFP_KERNEL);
	if (!bp->hwrm_cmd_resp_addr)
		return -ENOMEM;

	return 0;
}