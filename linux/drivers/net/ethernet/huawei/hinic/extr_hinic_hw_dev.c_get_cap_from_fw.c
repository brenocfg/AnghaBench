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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_pfhwdev {int /*<<< orphan*/  pf_to_mgmt; struct hinic_hwdev hwdev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_dev_cap {int dummy; } ;
typedef  int /*<<< orphan*/  dev_cap ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_CFG_NIC_CAP ; 
 int /*<<< orphan*/  HINIC_MGMT_MSG_SYNC ; 
 int /*<<< orphan*/  HINIC_MOD_CFGM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int get_capability (struct hinic_hwdev*,struct hinic_dev_cap*) ; 
 int hinic_msg_to_mgmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hinic_dev_cap*,int,struct hinic_dev_cap*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_cap_from_fw(struct hinic_pfhwdev *pfhwdev)
{
	struct hinic_hwdev *hwdev = &pfhwdev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_dev_cap dev_cap;
	u16 in_len, out_len;
	int err;

	in_len = 0;
	out_len = sizeof(dev_cap);

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_CFGM,
				HINIC_CFG_NIC_CAP, &dev_cap, in_len, &dev_cap,
				&out_len, HINIC_MGMT_MSG_SYNC);
	if (err) {
		dev_err(&pdev->dev, "Failed to get capability from FW\n");
		return err;
	}

	return get_capability(hwdev, &dev_cap);
}