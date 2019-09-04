#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ngene {int cmd_timeout_workaround; TYPE_2__* pci_dev; TYPE_1__* card_info; } ;
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int ngene_command_load_firmware (struct ngene*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char*,struct device*) ; 

__attribute__((used)) static int ngene_load_firm(struct ngene *dev)
{
	struct device *pdev = &dev->pci_dev->dev;
	u32 size;
	const struct firmware *fw = NULL;
	u8 *ngene_fw;
	char *fw_name;
	int err, version;

	version = dev->card_info->fw_version;

	switch (version) {
	default:
	case 15:
		version = 15;
		size = 23466;
		fw_name = "ngene_15.fw";
		dev->cmd_timeout_workaround = true;
		break;
	case 16:
		size = 23498;
		fw_name = "ngene_16.fw";
		dev->cmd_timeout_workaround = true;
		break;
	case 17:
		size = 24446;
		fw_name = "ngene_17.fw";
		dev->cmd_timeout_workaround = true;
		break;
	case 18:
		size = 0;
		fw_name = "ngene_18.fw";
		break;
	}

	if (request_firmware(&fw, fw_name, &dev->pci_dev->dev) < 0) {
		dev_err(pdev, "Could not load firmware file %s.\n", fw_name);
		dev_info(pdev, "Copy %s to your hotplug directory!\n",
			 fw_name);
		return -1;
	}
	if (size == 0)
		size = fw->size;
	if (size != fw->size) {
		dev_err(pdev, "Firmware %s has invalid size!", fw_name);
		err = -1;
	} else {
		dev_info(pdev, "Loading firmware file %s.\n", fw_name);
		ngene_fw = (u8 *) fw->data;
		err = ngene_command_load_firmware(dev, ngene_fw, size);
	}

	release_firmware(fw);

	return err;
}