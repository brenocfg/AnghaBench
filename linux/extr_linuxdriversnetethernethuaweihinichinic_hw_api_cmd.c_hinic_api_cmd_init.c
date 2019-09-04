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
struct hinic_api_cmd_chain_attr {int chain_type; int /*<<< orphan*/  cell_size; int /*<<< orphan*/  num_cells; struct hinic_hwif* hwif; } ;
struct hinic_api_cmd_chain {int dummy; } ;
struct hinic_api_cmd_cell {int dummy; } ;
typedef  enum hinic_api_cmd_chain_type { ____Placeholder_hinic_api_cmd_chain_type } hinic_api_cmd_chain_type ;

/* Variables and functions */
 int /*<<< orphan*/  API_CHAIN_NUM_CELLS ; 
 int /*<<< orphan*/  API_CMD_CELL_SIZE (size_t) ; 
 int HINIC_API_CMD_MAX ; 
 int HINIC_API_CMD_WRITE_TO_MGMT_CPU ; 
 scalar_t__ IS_ERR (struct hinic_api_cmd_chain*) ; 
 int PTR_ERR (struct hinic_api_cmd_chain*) ; 
 struct hinic_api_cmd_chain* api_cmd_create_chain (struct hinic_api_cmd_chain_attr*) ; 
 int /*<<< orphan*/  api_cmd_destroy_chain (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

int hinic_api_cmd_init(struct hinic_api_cmd_chain **chain,
		       struct hinic_hwif *hwif)
{
	enum hinic_api_cmd_chain_type type, chain_type;
	struct hinic_api_cmd_chain_attr attr;
	struct pci_dev *pdev = hwif->pdev;
	size_t hw_cell_sz;
	int err;

	hw_cell_sz = sizeof(struct hinic_api_cmd_cell);

	attr.hwif = hwif;
	attr.num_cells  = API_CHAIN_NUM_CELLS;
	attr.cell_size  = API_CMD_CELL_SIZE(hw_cell_sz);

	chain_type = HINIC_API_CMD_WRITE_TO_MGMT_CPU;
	for ( ; chain_type < HINIC_API_CMD_MAX; chain_type++) {
		attr.chain_type = chain_type;

		if (chain_type != HINIC_API_CMD_WRITE_TO_MGMT_CPU)
			continue;

		chain[chain_type] = api_cmd_create_chain(&attr);
		if (IS_ERR(chain[chain_type])) {
			dev_err(&pdev->dev, "Failed to create chain %d\n",
				chain_type);
			err = PTR_ERR(chain[chain_type]);
			goto err_create_chain;
		}
	}

	return 0;

err_create_chain:
	type = HINIC_API_CMD_WRITE_TO_MGMT_CPU;
	for ( ; type < chain_type; type++) {
		if (type != HINIC_API_CMD_WRITE_TO_MGMT_CPU)
			continue;

		api_cmd_destroy_chain(chain[type]);
	}

	return err;
}