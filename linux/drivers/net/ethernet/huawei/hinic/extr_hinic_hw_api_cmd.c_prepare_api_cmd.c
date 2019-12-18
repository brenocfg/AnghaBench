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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_api_cmd_chain {size_t prod_idx; int chain_type; struct hinic_api_cmd_cell_ctxt* cell_ctxt; struct hinic_hwif* hwif; struct hinic_api_cmd_cell* curr_node; } ;
struct hinic_api_cmd_cell_ctxt {int /*<<< orphan*/  api_cmd_vaddr; } ;
struct hinic_api_cmd_cell {int desc; } ;
typedef  enum hinic_node_id { ____Placeholder_hinic_node_id } hinic_node_id ;

/* Variables and functions */
 int API_CMD_WRITE ; 
 int /*<<< orphan*/  API_TYPE ; 
 int /*<<< orphan*/  DEST ; 
 int HINIC_API_CMD_DESC_SET (int,int /*<<< orphan*/ ) ; 
#define  HINIC_API_CMD_WRITE_TO_MGMT_CPU 128 
 int /*<<< orphan*/  MGMT_BYPASS ; 
 int NO_BYPASS ; 
 int /*<<< orphan*/  RD_WR ; 
 int SGE_DATA ; 
 int /*<<< orphan*/  SIZE ; 
 int SIZE_4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOR_CHKSUM ; 
 int cpu_to_be64 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int xor_chksum_set (int*) ; 

__attribute__((used)) static void prepare_api_cmd(struct hinic_api_cmd_chain *chain,
			    enum hinic_node_id dest,
			    void *cmd, u16 cmd_size)
{
	struct hinic_api_cmd_cell *cell = chain->curr_node;
	struct hinic_api_cmd_cell_ctxt *cell_ctxt;
	struct hinic_hwif *hwif = chain->hwif;
	struct pci_dev *pdev = hwif->pdev;

	cell_ctxt = &chain->cell_ctxt[chain->prod_idx];

	switch (chain->chain_type) {
	case HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		cell->desc = HINIC_API_CMD_DESC_SET(SGE_DATA, API_TYPE)   |
			     HINIC_API_CMD_DESC_SET(API_CMD_WRITE, RD_WR) |
			     HINIC_API_CMD_DESC_SET(NO_BYPASS, MGMT_BYPASS);
		break;

	default:
		dev_err(&pdev->dev, "unknown Chain type\n");
		return;
	}

	cell->desc |= HINIC_API_CMD_DESC_SET(dest, DEST)        |
		      HINIC_API_CMD_DESC_SET(SIZE_4BYTES(cmd_size), SIZE);

	cell->desc |= HINIC_API_CMD_DESC_SET(xor_chksum_set(&cell->desc),
					     XOR_CHKSUM);

	/* The data in the HW should be in Big Endian Format */
	cell->desc = cpu_to_be64(cell->desc);

	memcpy(cell_ctxt->api_cmd_vaddr, cmd, cmd_size);
}