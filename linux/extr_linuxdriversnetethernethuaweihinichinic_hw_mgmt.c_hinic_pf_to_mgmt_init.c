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
struct hinic_hwdev {int /*<<< orphan*/  aeqs; } ;
struct hinic_pfhwdev {struct hinic_hwdev hwdev; } ;
struct hinic_pf_to_mgmt {int /*<<< orphan*/  cmd_chain; scalar_t__ sync_msg_id; int /*<<< orphan*/  sync_msg_lock; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_MSG_FROM_MGMT_CPU ; 
 int alloc_msg_buf (struct hinic_pf_to_mgmt*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hinic_aeq_register_hw_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hinic_pf_to_mgmt*,int /*<<< orphan*/ ) ; 
 int hinic_api_cmd_init (int /*<<< orphan*/ ,struct hinic_hwif*) ; 
 int /*<<< orphan*/  mgmt_msg_aeqe_handler ; 
 struct hinic_pfhwdev* mgmt_to_pfhwdev (struct hinic_pf_to_mgmt*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

int hinic_pf_to_mgmt_init(struct hinic_pf_to_mgmt *pf_to_mgmt,
			  struct hinic_hwif *hwif)
{
	struct hinic_pfhwdev *pfhwdev = mgmt_to_pfhwdev(pf_to_mgmt);
	struct hinic_hwdev *hwdev = &pfhwdev->hwdev;
	struct pci_dev *pdev = hwif->pdev;
	int err;

	pf_to_mgmt->hwif = hwif;

	sema_init(&pf_to_mgmt->sync_msg_lock, 1);
	pf_to_mgmt->sync_msg_id = 0;

	err = alloc_msg_buf(pf_to_mgmt);
	if (err) {
		dev_err(&pdev->dev, "Failed to allocate msg buffers\n");
		return err;
	}

	err = hinic_api_cmd_init(pf_to_mgmt->cmd_chain, hwif);
	if (err) {
		dev_err(&pdev->dev, "Failed to initialize cmd chains\n");
		return err;
	}

	hinic_aeq_register_hw_cb(&hwdev->aeqs, HINIC_MSG_FROM_MGMT_CPU,
				 pf_to_mgmt,
				 mgmt_msg_aeqe_handler);
	return 0;
}