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
typedef  int /*<<< orphan*/  vlan_cfg ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_vlan_cfg {scalar_t__ status; int /*<<< orphan*/  vlan_rx_offload; int /*<<< orphan*/  func_id; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_SET_RX_VLAN_OFFLOAD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_vlan_cfg*,int,struct hinic_vlan_cfg*,int /*<<< orphan*/ *) ; 

int hinic_set_rx_vlan_offload(struct hinic_dev *nic_dev, u8 en)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_vlan_cfg vlan_cfg;
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u16 out_size;
	int err;

	if (!hwdev)
		return -EINVAL;

	hwif = hwdev->hwif;
	pdev = hwif->pdev;
	vlan_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	vlan_cfg.vlan_rx_offload = en;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RX_VLAN_OFFLOAD,
				 &vlan_cfg, sizeof(vlan_cfg),
				 &vlan_cfg, &out_size);
	if (err || !out_size || vlan_cfg.status) {
		dev_err(&pdev->dev,
			"Failed to set rx vlan offload, err: %d, status: 0x%x, out size: 0x%x\n",
			err, vlan_cfg.status, out_size);
		return -EINVAL;
	}

	return 0;
}