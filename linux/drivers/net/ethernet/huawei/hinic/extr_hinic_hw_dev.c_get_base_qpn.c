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
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_cmd_base_qpn {int qpn; scalar_t__ status; int /*<<< orphan*/  func_idx; } ;
typedef  int /*<<< orphan*/  cmd_base_qpn ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_GET_GLOBAL_QPN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_cmd_base_qpn*,int,struct hinic_cmd_base_qpn*,int*) ; 

__attribute__((used)) static int get_base_qpn(struct hinic_hwdev *hwdev, u16 *base_qpn)
{
	struct hinic_cmd_base_qpn cmd_base_qpn;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u16 out_size;
	int err;

	cmd_base_qpn.func_idx = HINIC_HWIF_FUNC_IDX(hwif);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_GLOBAL_QPN,
				 &cmd_base_qpn, sizeof(cmd_base_qpn),
				 &cmd_base_qpn, &out_size);
	if (err || (out_size != sizeof(cmd_base_qpn)) || cmd_base_qpn.status) {
		dev_err(&pdev->dev, "Failed to get base qpn, status = %d\n",
			cmd_base_qpn.status);
		return -EFAULT;
	}

	*base_qpn = cmd_base_qpn.qpn;
	return 0;
}