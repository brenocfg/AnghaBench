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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  temp_key ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rss_template_key {int /*<<< orphan*/  key; scalar_t__ status; int /*<<< orphan*/  template_id; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_GET_RSS_TEMPLATE_TBL ; 
 int /*<<< orphan*/  HINIC_RSS_KEY_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_rss_template_key*,int,struct hinic_rss_template_key*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hinic_rss_get_template_tbl(struct hinic_dev *nic_dev, u32 tmpl_idx,
			       u8 *temp)
{
	struct hinic_rss_template_key temp_key = { 0 };
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u16 out_size = sizeof(temp_key);
	int err;

	if (!hwdev || !temp)
		return -EINVAL;

	hwif = hwdev->hwif;
	pdev = hwif->pdev;

	temp_key.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	temp_key.template_id = tmpl_idx;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_RSS_TEMPLATE_TBL,
				 &temp_key, sizeof(temp_key),
				 &temp_key, &out_size);
	if (err || !out_size || temp_key.status) {
		dev_err(&pdev->dev, "Failed to set hash key, err: %d, status: 0x%x, out size: 0x%x\n",
			err, temp_key.status, out_size);
		return -EINVAL;
	}

	memcpy(temp, temp_key.key, HINIC_RSS_KEY_SIZE);

	return 0;
}