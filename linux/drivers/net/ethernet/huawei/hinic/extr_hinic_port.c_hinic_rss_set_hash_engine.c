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
struct hinic_rss_engine_type {scalar_t__ status; void* template_id; void* hash_engine; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  rss_engine ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_SET_RSS_HASH_ENGINE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_rss_engine_type*,int,struct hinic_rss_engine_type*,int /*<<< orphan*/ *) ; 

int hinic_rss_set_hash_engine(struct hinic_dev *nic_dev, u8 template_id,
			      u8 type)
{
	struct hinic_rss_engine_type rss_engine = { 0 };
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u16 out_size;
	int err;

	rss_engine.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	rss_engine.hash_engine = type;
	rss_engine.template_id = template_id;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RSS_HASH_ENGINE,
				 &rss_engine, sizeof(rss_engine),
				 &rss_engine, &out_size);
	if (err || !out_size || rss_engine.status) {
		dev_err(&pdev->dev,
			"Failed to set hash engine, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rss_engine.status, out_size);
		return -EINVAL;
	}

	return 0;
}