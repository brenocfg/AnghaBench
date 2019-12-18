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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_api_cmd_chain {int chain_type; struct hinic_api_cmd_cell_ctxt* cell_ctxt; struct hinic_hwif* hwif; } ;
struct hinic_api_cmd_cell_ctxt {int /*<<< orphan*/  api_cmd_paddr; int /*<<< orphan*/ * api_cmd_vaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_cmd_paddr; } ;
struct hinic_api_cmd_cell {TYPE_1__ write; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  API_CMD_BUF_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HINIC_API_CMD_WRITE_TO_MGMT_CPU 128 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmd_buf (struct hinic_api_cmd_chain*,int) ; 

__attribute__((used)) static int alloc_cmd_buf(struct hinic_api_cmd_chain *chain,
			 struct hinic_api_cmd_cell *cell, int cell_idx)
{
	struct hinic_api_cmd_cell_ctxt *cell_ctxt;
	struct hinic_hwif *hwif = chain->hwif;
	struct pci_dev *pdev = hwif->pdev;
	dma_addr_t cmd_paddr;
	u8 *cmd_vaddr;
	int err = 0;

	cmd_vaddr = dma_alloc_coherent(&pdev->dev, API_CMD_BUF_SIZE,
				       &cmd_paddr, GFP_KERNEL);
	if (!cmd_vaddr) {
		dev_err(&pdev->dev, "Failed to allocate API CMD DMA memory\n");
		return -ENOMEM;
	}

	cell_ctxt = &chain->cell_ctxt[cell_idx];

	cell_ctxt->api_cmd_vaddr = cmd_vaddr;
	cell_ctxt->api_cmd_paddr = cmd_paddr;

	/* set the cmd DMA address in the cell */
	switch (chain->chain_type) {
	case HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		/* The data in the HW should be in Big Endian Format */
		cell->write.hw_cmd_paddr = cpu_to_be64(cmd_paddr);
		break;

	default:
		dev_err(&pdev->dev, "Unsupported API CMD chain type\n");
		free_cmd_buf(chain, cell_idx);
		err = -EINVAL;
		break;
	}

	return err;
}