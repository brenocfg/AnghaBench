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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rss_key {scalar_t__ status; int /*<<< orphan*/  key; int /*<<< orphan*/  template_id; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  rss_key ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_SET_RSS_TEMPLATE_TBL ; 
 int /*<<< orphan*/  HINIC_RSS_KEY_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_rss_key*,int,struct hinic_rss_key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int hinic_rss_set_template_tbl(struct hinic_dev *nic_dev, u32 template_id,
			       const u8 *temp)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct hinic_rss_key rss_key = { 0 };
	struct pci_dev *pdev = hwif->pdev;
	u16 out_size;
	int err;

	rss_key.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	rss_key.template_id = template_id;
	memcpy(rss_key.key, temp, HINIC_RSS_KEY_SIZE);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RSS_TEMPLATE_TBL,
				 &rss_key, sizeof(rss_key),
				 &rss_key, &out_size);
	if (err || !out_size || rss_key.status) {
		dev_err(&pdev->dev,
			"Failed to set rss hash key, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rss_key.status, out_size);
		return -EINVAL;
	}

	return 0;
}