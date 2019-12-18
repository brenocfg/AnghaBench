#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct mei_me_hw {TYPE_1__* cfg; } ;
struct mei_fw_status {int count; int /*<<< orphan*/ * status; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct mei_fw_status fw_status; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEI_FW_STATUS_MAX ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mei_pci_cfg_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_me_fw_status(struct mei_device *dev,
			    struct mei_fw_status *fw_status)
{
	struct pci_dev *pdev = to_pci_dev(dev->dev);
	struct mei_me_hw *hw = to_me_hw(dev);
	const struct mei_fw_status *fw_src = &hw->cfg->fw_status;
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