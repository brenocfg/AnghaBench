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
struct hinic_api_cmd_chain {size_t cell_size; int chain_type; struct hinic_api_cmd_cell_ctxt* cell_ctxt; struct hinic_hwif* hwif; } ;
struct hinic_api_cmd_cell_ctxt {scalar_t__ api_cmd_vaddr; int /*<<< orphan*/  cell_paddr; struct hinic_api_cmd_cell* cell_vaddr; } ;
struct hinic_api_cmd_cell {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
#define  HINIC_API_CMD_WRITE_TO_MGMT_CPU 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,struct hinic_api_cmd_cell*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmd_buf (struct hinic_api_cmd_chain*,int) ; 

__attribute__((used)) static void api_cmd_destroy_cell(struct hinic_api_cmd_chain *chain,
				 int cell_idx)
{
	struct hinic_api_cmd_cell_ctxt *cell_ctxt;
	struct hinic_hwif *hwif = chain->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_api_cmd_cell *node;
	dma_addr_t node_paddr;
	size_t node_size;

	cell_ctxt = &chain->cell_ctxt[cell_idx];

	node = cell_ctxt->cell_vaddr;
	node_paddr = cell_ctxt->cell_paddr;
	node_size = chain->cell_size;

	if (cell_ctxt->api_cmd_vaddr) {
		switch (chain->chain_type) {
		case HINIC_API_CMD_WRITE_TO_MGMT_CPU:
			free_cmd_buf(chain, cell_idx);
			break;
		default:
			dev_err(&pdev->dev, "Unsupported API CMD chain type\n");
			break;
		}

		dma_free_coherent(&pdev->dev, node_size, node,
				  node_paddr);
	}
}