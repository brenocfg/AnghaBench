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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
struct hinic_checksum_offload {scalar_t__ status; int /*<<< orphan*/  rx_csum_offload; int /*<<< orphan*/  func_id; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  rx_csum_cfg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_SET_RX_CSUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_checksum_offload*,int,struct hinic_checksum_offload*,int /*<<< orphan*/ *) ; 

int hinic_set_rx_csum_offload(struct hinic_dev *nic_dev, u32 en)
{
	struct hinic_checksum_offload rx_csum_cfg = {0};
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif;
	struct pci_dev *pdev;
	u16 out_size;
	int err;

	if (!hwdev)
		return -EINVAL;

	hwif = hwdev->hwif;
	pdev = hwif->pdev;
	rx_csum_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwif);
	rx_csum_cfg.rx_csum_offload = en;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RX_CSUM,
				 &rx_csum_cfg, sizeof(rx_csum_cfg),
				 &rx_csum_cfg, &out_size);
	if (err || !out_size || rx_csum_cfg.status) {
		dev_err(&pdev->dev,
			"Failed to set rx csum offload, ret = %d\n",
			rx_csum_cfg.status);
		return -EINVAL;
	}

	return 0;
}