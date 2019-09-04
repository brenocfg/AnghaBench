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
struct smi_settings {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  BCM2835_SMI_IOC_ADDRESS 130 
#define  BCM2835_SMI_IOC_GET_SETTINGS 129 
#define  BCM2835_SMI_IOC_WRITE_SETTINGS 128 
 long ENOTTY ; 
 struct smi_settings* bcm2835_smi_get_settings_from_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_smi_set_address (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bcm2835_smi_set_regs_from_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (struct smi_settings*,void*,int) ; 
 int /*<<< orphan*/  copy_to_user (void*,struct smi_settings*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* inst ; 
 int /*<<< orphan*/  smi_inst ; 

__attribute__((used)) static long
bcm2835_smi_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret = 0;

	dev_info(inst->dev, "serving ioctl...");

	switch (cmd) {
	case BCM2835_SMI_IOC_GET_SETTINGS:{
		struct smi_settings *settings;

		dev_info(inst->dev, "Reading SMI settings to user.");
		settings = bcm2835_smi_get_settings_from_regs(smi_inst);
		if (copy_to_user((void *)arg, settings,
				 sizeof(struct smi_settings)))
			dev_err(inst->dev, "settings copy failed.");
		break;
	}
	case BCM2835_SMI_IOC_WRITE_SETTINGS:{
		struct smi_settings *settings;

		dev_info(inst->dev, "Setting user's SMI settings.");
		settings = bcm2835_smi_get_settings_from_regs(smi_inst);
		if (copy_from_user(settings, (void *)arg,
				   sizeof(struct smi_settings)))
			dev_err(inst->dev, "settings copy failed.");
		else
			bcm2835_smi_set_regs_from_settings(smi_inst);
		break;
	}
	case BCM2835_SMI_IOC_ADDRESS:
		dev_info(inst->dev, "SMI address set: 0x%02x", (int)arg);
		bcm2835_smi_set_address(smi_inst, arg);
		break;
	default:
		dev_err(inst->dev, "invalid ioctl cmd: %d", cmd);
		ret = -ENOTTY;
		break;
	}

	return ret;
}