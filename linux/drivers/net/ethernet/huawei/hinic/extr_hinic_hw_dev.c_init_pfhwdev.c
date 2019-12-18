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
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_pfhwdev {int /*<<< orphan*/  pf_to_mgmt; struct hinic_hwdev hwdev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_MOD_L2NIC ; 
 int /*<<< orphan*/  HINIC_PF_MGMT_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hinic_pf_to_mgmt_init (int /*<<< orphan*/ *,struct hinic_hwif*) ; 
 int /*<<< orphan*/  hinic_register_mgmt_msg_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hinic_pfhwdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_set_pf_action (struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic_mgmt_msg_handler ; 

__attribute__((used)) static int init_pfhwdev(struct hinic_pfhwdev *pfhwdev)
{
	struct hinic_hwdev *hwdev = &pfhwdev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	int err;

	err = hinic_pf_to_mgmt_init(&pfhwdev->pf_to_mgmt, hwif);
	if (err) {
		dev_err(&pdev->dev, "Failed to initialize PF to MGMT channel\n");
		return err;
	}

	hinic_register_mgmt_msg_cb(&pfhwdev->pf_to_mgmt, HINIC_MOD_L2NIC,
				   pfhwdev, nic_mgmt_msg_handler);

	hinic_set_pf_action(hwif, HINIC_PF_MGMT_ACTIVE);
	return 0;
}