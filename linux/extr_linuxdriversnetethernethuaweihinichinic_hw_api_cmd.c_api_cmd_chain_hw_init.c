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
struct hinic_api_cmd_chain {struct hinic_hwif* hwif; } ;

/* Variables and functions */
 int /*<<< orphan*/  api_cmd_chain_hw_clean (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  api_cmd_ctrl_init (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  api_cmd_head_init (struct hinic_api_cmd_chain*) ; 
 int api_cmd_hw_restart (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  api_cmd_set_num_cells (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  api_cmd_set_status_addr (struct hinic_api_cmd_chain*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int api_cmd_chain_hw_init(struct hinic_api_cmd_chain *chain)
{
	struct hinic_hwif *hwif = chain->hwif;
	struct pci_dev *pdev = hwif->pdev;
	int err;

	api_cmd_chain_hw_clean(chain);

	api_cmd_set_status_addr(chain);

	err = api_cmd_hw_restart(chain);
	if (err) {
		dev_err(&pdev->dev, "Failed to restart API CMD HW\n");
		return err;
	}

	api_cmd_ctrl_init(chain);
	api_cmd_set_num_cells(chain);
	api_cmd_head_init(chain);
	return 0;
}