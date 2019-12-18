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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  template_mgmt ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rss_template_mgmt {scalar_t__ status; int /*<<< orphan*/  cmd; int /*<<< orphan*/  template_id; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_RSS_TEMP_MGR ; 
 int /*<<< orphan*/  NIC_RSS_CMD_TEMP_FREE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_rss_template_mgmt*,int,struct hinic_rss_template_mgmt*,int /*<<< orphan*/ *) ; 

int hinic_rss_template_free(struct hinic_dev *nic_dev, u8 tmpl_idx)
{
	struct hinic_rss_template_mgmt template_mgmt = { 0 };
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u16 out_size;
	int err;

	template_mgmt.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	template_mgmt.template_id = tmpl_idx;
	template_mgmt.cmd = NIC_RSS_CMD_TEMP_FREE;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_RSS_TEMP_MGR,
				 &template_mgmt, sizeof(template_mgmt),
				 &template_mgmt, &out_size);
	if (err || !out_size || template_mgmt.status) {
		dev_err(&pdev->dev, "Failed to free rss template, err: %d, status: 0x%x, out size: 0x%x\n",
			err, template_mgmt.status, out_size);
		return -EINVAL;
	}

	return 0;
}