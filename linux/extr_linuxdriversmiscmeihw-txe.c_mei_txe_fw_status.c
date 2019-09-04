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
struct pci_dev {int dummy; } ;
struct mei_fw_status {int count; int /*<<< orphan*/ * status; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEI_FW_STATUS_MAX ; 
 struct mei_fw_status mei_txe_fw_sts ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mei_pci_cfg_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_txe_fw_status(struct mei_device *dev,
			     struct mei_fw_status *fw_status)
{
	const struct mei_fw_status *fw_src = &mei_txe_fw_sts;
	struct pci_dev *pdev = to_pci_dev(dev->dev);
	int ret;
	int i;

	if (!fw_status)
		return -EINVAL;

	fw_status->count = fw_src->count;
	for (i = 0; i < fw_src->count && i < MEI_FW_STATUS_MAX; i++) {
		ret = pci_read_config_dword(pdev, fw_src->status[i],
					    &fw_status->status[i]);
		trace_mei_pci_cfg_read(dev->dev, "PCI_CFG_HSF_X",
				       fw_src->status[i],
				       fw_status->status[i]);
		if (ret)
			return ret;
	}

	return 0;
}