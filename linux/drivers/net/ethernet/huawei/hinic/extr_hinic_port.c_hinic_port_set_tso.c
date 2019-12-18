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
typedef  int /*<<< orphan*/  tso_cfg ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_tso_config {int tso_en; scalar_t__ status; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  enum hinic_tso_state { ____Placeholder_hinic_tso_state } hinic_tso_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_SET_TSO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_tso_config*,int,struct hinic_tso_config*,int*) ; 

int hinic_port_set_tso(struct hinic_dev *nic_dev, enum hinic_tso_state state)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct hinic_tso_config tso_cfg = {0};
	struct pci_dev *pdev = hwif->pdev;
	u16 out_size;
	int err;

	tso_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	tso_cfg.tso_en = state;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_TSO,
				 &tso_cfg, sizeof(tso_cfg),
				 &tso_cfg, &out_size);
	if (err || out_size != sizeof(tso_cfg) || tso_cfg.status) {
		dev_err(&pdev->dev,
			"Failed to set port tso, ret = %d\n",
			tso_cfg.status);
		return -EINVAL;
	}

	return 0;
}