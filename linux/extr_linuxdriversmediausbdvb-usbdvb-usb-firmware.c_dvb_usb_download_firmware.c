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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct dvb_usb_device_properties {int usb_ctrl; int (* download_firmware ) (struct usb_device*,struct firmware const*) ;int /*<<< orphan*/  firmware; } ;

/* Variables and functions */
#define  CYPRESS_AN2135 131 
#define  CYPRESS_AN2235 130 
#define  CYPRESS_FX2 129 
#define  DEVICE_SPECIFIC 128 
 int EINVAL ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct usb_device*,struct firmware const*) ; 
 int usb_cypress_load_firmware (struct usb_device*,struct firmware const*,int) ; 

int dvb_usb_download_firmware(struct usb_device *udev, struct dvb_usb_device_properties *props)
{
	int ret;
	const struct firmware *fw = NULL;

	if ((ret = request_firmware(&fw, props->firmware, &udev->dev)) != 0) {
		err("did not find the firmware file '%s' (status %d). You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware",
			props->firmware,ret);
		return ret;
	}

	info("downloading firmware from file '%s'",props->firmware);

	switch (props->usb_ctrl) {
		case CYPRESS_AN2135:
		case CYPRESS_AN2235:
		case CYPRESS_FX2:
			ret = usb_cypress_load_firmware(udev, fw, props->usb_ctrl);
			break;
		case DEVICE_SPECIFIC:
			if (props->download_firmware)
				ret = props->download_firmware(udev,fw);
			else {
				err("BUG: driver didn't specified a download_firmware-callback, although it claims to have a DEVICE_SPECIFIC one.");
				ret = -EINVAL;
			}
			break;
		default:
			ret = -EINVAL;
			break;
	}

	release_firmware(fw);
	return ret;
}