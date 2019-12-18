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
struct hinic_cmd_fw_ctxt {scalar_t__ status; int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  func_idx; } ;
typedef  int /*<<< orphan*/  fw_ctxt ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_IS_PF (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_IS_PPF (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_FWCTXT_INIT ; 
 int /*<<< orphan*/  HINIC_RX_BUF_SZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_cmd_fw_ctxt*,int,struct hinic_cmd_fw_ctxt*,int*) ; 

__attribute__((used)) static int init_fw_ctxt(struct hinic_hwdev *hwdev)
{
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	struct hinic_cmd_fw_ctxt fw_ctxt;
	u16 out_size;
	int err;

	if (!HINIC_IS_PF(hwif) && !HINIC_IS_PPF(hwif)) {
		dev_err(&pdev->dev, "Unsupported PCI Function type\n");
		return -EINVAL;
	}

	fw_ctxt.func_idx = HINIC_HWIF_FUNC_IDX(hwif);
	fw_ctxt.rx_buf_sz = HINIC_RX_BUF_SZ;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_FWCTXT_INIT,
				 &fw_ctxt, sizeof(fw_ctxt),
				 &fw_ctxt, &out_size);
	if (err || (out_size != sizeof(fw_ctxt)) || fw_ctxt.status) {
		dev_err(&pdev->dev, "Failed to init FW ctxt, ret = %d\n",
			fw_ctxt.status);
		return -EFAULT;
	}

	return 0;
}