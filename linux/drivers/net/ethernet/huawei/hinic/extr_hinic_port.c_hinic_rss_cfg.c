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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rss_config {scalar_t__ status; scalar_t__ rq_priority_number; void* template_id; void* rss_en; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  rss_cfg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_RSS_CFG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_rss_config*,int,struct hinic_rss_config*,int /*<<< orphan*/ *) ; 

int hinic_rss_cfg(struct hinic_dev *nic_dev, u8 rss_en, u8 template_id)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_rss_config rss_cfg = { 0 };
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u16 out_size;
	int err;

	rss_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	rss_cfg.rss_en = rss_en;
	rss_cfg.template_id = template_id;
	rss_cfg.rq_priority_number = 0;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_RSS_CFG,
				 &rss_cfg, sizeof(rss_cfg),
				 &rss_cfg, &out_size);
	if (err || !out_size || rss_cfg.status) {
		dev_err(&pdev->dev,
			"Failed to set rss cfg, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rss_cfg.status, out_size);
		return -EINVAL;
	}

	return 0;
}