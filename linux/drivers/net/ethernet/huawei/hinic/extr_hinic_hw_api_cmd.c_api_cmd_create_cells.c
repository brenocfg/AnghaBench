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
struct hinic_api_cmd_chain {int num_cells; int /*<<< orphan*/  head_node; int /*<<< orphan*/  curr_node; int /*<<< orphan*/  head_cell_paddr; struct hinic_hwif* hwif; } ;
struct hinic_api_cmd_cell {int /*<<< orphan*/  next_cell_paddr; } ;

/* Variables and functions */
 int api_cmd_create_cell (struct hinic_api_cmd_chain*,int,struct hinic_api_cmd_cell*,struct hinic_api_cmd_cell**) ; 
 int /*<<< orphan*/  api_cmd_destroy_cells (struct hinic_api_cmd_chain*,int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int api_cmd_create_cells(struct hinic_api_cmd_chain *chain)
{
	struct hinic_api_cmd_cell *node = NULL, *pre_node = NULL;
	struct hinic_hwif *hwif = chain->hwif;
	struct pci_dev *pdev = hwif->pdev;
	int err, cell_idx;

	for (cell_idx = 0; cell_idx < chain->num_cells; cell_idx++) {
		err = api_cmd_create_cell(chain, cell_idx, pre_node, &node);
		if (err) {
			dev_err(&pdev->dev, "Failed to create API CMD cell\n");
			goto err_create_cell;
		}

		pre_node = node;
	}

	/* set the Final node to point on the start */
	node->next_cell_paddr = cpu_to_be64(chain->head_cell_paddr);

	/* set the current node to be the head */
	chain->curr_node = chain->head_node;
	return 0;

err_create_cell:
	api_cmd_destroy_cells(chain, cell_idx);
	return err;
}