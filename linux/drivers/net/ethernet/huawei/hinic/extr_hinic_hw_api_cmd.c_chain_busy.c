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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_api_cmd_chain {int chain_type; int /*<<< orphan*/  cons_idx; int /*<<< orphan*/  prod_idx; struct hinic_hwif* hwif; } ;

/* Variables and functions */
 int EBUSY ; 
#define  HINIC_API_CMD_WRITE_TO_MGMT_CPU 128 
 int /*<<< orphan*/  MASKED_IDX (struct hinic_api_cmd_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  get_hw_cons_idx (struct hinic_api_cmd_chain*) ; 

__attribute__((used)) static int chain_busy(struct hinic_api_cmd_chain *chain)
{
	struct hinic_hwif *hwif = chain->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u32 prod_idx;

	switch (chain->chain_type) {
	case HINIC_API_CMD_WRITE_TO_MGMT_CPU:
		chain->cons_idx = get_hw_cons_idx(chain);
		prod_idx = chain->prod_idx;

		/* check for a space for a new command */
		if (chain->cons_idx == MASKED_IDX(chain, prod_idx + 1)) {
			dev_err(&pdev->dev, "API CMD chain %d is busy\n",
				chain->chain_type);
			return -EBUSY;
		}
		break;

	default:
		dev_err(&pdev->dev, "Unknown API CMD Chain type\n");
		break;
	}

	return 0;
}