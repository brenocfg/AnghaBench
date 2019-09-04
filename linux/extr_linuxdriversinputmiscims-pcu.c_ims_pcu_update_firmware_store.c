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
struct usb_interface {int dummy; } ;
struct ims_pcu {int /*<<< orphan*/  cmd_mutex; scalar_t__ bootloader_mode; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMS_PCU_FIRMWARE_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int ims_pcu_handle_firmware_update (struct ims_pcu*,struct firmware const*) ; 
 int ims_pcu_switch_to_bootloader (struct ims_pcu*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_ihex_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct ims_pcu* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t ims_pcu_update_firmware_store(struct device *dev,
					     struct device_attribute *dattr,
					     const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct ims_pcu *pcu = usb_get_intfdata(intf);
	const struct firmware *fw = NULL;
	int value;
	int error;

	error = kstrtoint(buf, 0, &value);
	if (error)
		return error;

	if (value != 1)
		return -EINVAL;

	error = mutex_lock_interruptible(&pcu->cmd_mutex);
	if (error)
		return error;

	error = request_ihex_firmware(&fw, IMS_PCU_FIRMWARE_NAME, pcu->dev);
	if (error) {
		dev_err(pcu->dev, "Failed to request firmware %s, error: %d\n",
			IMS_PCU_FIRMWARE_NAME, error);
		goto out;
	}

	/*
	 * If we are already in bootloader mode we can proceed with
	 * flashing the firmware.
	 *
	 * If we are in application mode, then we need to switch into
	 * bootloader mode, which will cause the device to disconnect
	 * and reconnect as different device.
	 */
	if (pcu->bootloader_mode)
		error = ims_pcu_handle_firmware_update(pcu, fw);
	else
		error = ims_pcu_switch_to_bootloader(pcu);

	release_firmware(fw);

out:
	mutex_unlock(&pcu->cmd_mutex);
	return error ?: count;
}