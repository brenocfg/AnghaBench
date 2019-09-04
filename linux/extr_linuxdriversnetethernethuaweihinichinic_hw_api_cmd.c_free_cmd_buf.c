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
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_api_cmd_chain {struct hinic_api_cmd_cell_ctxt* cell_ctxt; struct hinic_hwif* hwif; } ;
struct hinic_api_cmd_cell_ctxt {int /*<<< orphan*/  api_cmd_paddr; int /*<<< orphan*/  api_cmd_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_CMD_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_cmd_buf(struct hinic_api_cmd_chain *chain, int cell_idx)
{
	struct hinic_api_cmd_cell_ctxt *cell_ctxt;
	struct hinic_hwif *hwif = chain->hwif;
	struct pci_dev *pdev = hwif->pdev;

	cell_ctxt = &chain->cell_ctxt[cell_idx];

	dma_free_coherent(&pdev->dev, API_CMD_BUF_SIZE,
			  cell_ctxt->api_cmd_vaddr,
			  cell_ctxt->api_cmd_paddr);
}