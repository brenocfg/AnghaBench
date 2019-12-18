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
struct hinic_pf_to_mgmt {int /*<<< orphan*/  sync_msg_buf; int /*<<< orphan*/  recv_resp_msg_from_mgmt; int /*<<< orphan*/  recv_msg_from_mgmt; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_PF_MGMT_BUF_SIZE ; 
 int alloc_recv_msg (struct hinic_pf_to_mgmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_msg_buf(struct hinic_pf_to_mgmt *pf_to_mgmt)
{
	struct hinic_hwif *hwif = pf_to_mgmt->hwif;
	struct pci_dev *pdev = hwif->pdev;
	int err;

	err = alloc_recv_msg(pf_to_mgmt,
			     &pf_to_mgmt->recv_msg_from_mgmt);
	if (err) {
		dev_err(&pdev->dev, "Failed to allocate recv msg\n");
		return err;
	}

	err = alloc_recv_msg(pf_to_mgmt,
			     &pf_to_mgmt->recv_resp_msg_from_mgmt);
	if (err) {
		dev_err(&pdev->dev, "Failed to allocate resp recv msg\n");
		return err;
	}

	pf_to_mgmt->sync_msg_buf = devm_kzalloc(&pdev->dev,
						MAX_PF_MGMT_BUF_SIZE,
						GFP_KERNEL);
	if (!pf_to_mgmt->sync_msg_buf)
		return -ENOMEM;

	return 0;
}