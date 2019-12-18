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
struct TYPE_2__ {int brightness; int contrast; int hue; int saturation; int sharpness; } ;
struct hdpvr_device {char* usbc_buf; int fw_ver; int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; int /*<<< orphan*/  flags; TYPE_1__ options; } ;

/* Variables and functions */
 int ENOMEM ; 
#define  HDPVR_FIRMWARE_VERSION 132 
#define  HDPVR_FIRMWARE_VERSION_0X12 131 
#define  HDPVR_FIRMWARE_VERSION_0X15 130 
#define  HDPVR_FIRMWARE_VERSION_0X1E 129 
#define  HDPVR_FIRMWARE_VERSION_AC3 128 
 int /*<<< orphan*/  HDPVR_FLAG_AC3_CAP ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  challenge (char*) ; 
 int /*<<< orphan*/  hdpvr_debug ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,char*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int device_authorization(struct hdpvr_device *dev)
{

	int ret, retval = -ENOMEM;
	char request_type = 0x38, rcv_request = 0x81;
	char *response;

	mutex_lock(&dev->usbc_mutex);
	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      rcv_request, 0x80 | request_type,
			      0x0400, 0x0003,
			      dev->usbc_buf, 46,
			      10000);
	if (ret != 46) {
		v4l2_err(&dev->v4l2_dev,
			 "unexpected answer of status request, len %d\n", ret);
		goto unlock;
	}
#ifdef HDPVR_DEBUG
	else {
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "Status request returned, len %d: %46ph\n",
			 ret, dev->usbc_buf);
	}
#endif

	dev->fw_ver = dev->usbc_buf[1];

	dev->usbc_buf[46] = '\0';
	v4l2_info(&dev->v4l2_dev, "firmware version 0x%x dated %s\n",
			  dev->fw_ver, &dev->usbc_buf[2]);

	if (dev->fw_ver > 0x15) {
		dev->options.brightness	= 0x80;
		dev->options.contrast	= 0x40;
		dev->options.hue	= 0xf;
		dev->options.saturation	= 0x40;
		dev->options.sharpness	= 0x80;
	}

	switch (dev->fw_ver) {
	case HDPVR_FIRMWARE_VERSION:
		dev->flags &= ~HDPVR_FLAG_AC3_CAP;
		break;
	case HDPVR_FIRMWARE_VERSION_AC3:
	case HDPVR_FIRMWARE_VERSION_0X12:
	case HDPVR_FIRMWARE_VERSION_0X15:
	case HDPVR_FIRMWARE_VERSION_0X1E:
		dev->flags |= HDPVR_FLAG_AC3_CAP;
		break;
	default:
		v4l2_info(&dev->v4l2_dev, "untested firmware, the driver might not work.\n");
		if (dev->fw_ver >= HDPVR_FIRMWARE_VERSION_AC3)
			dev->flags |= HDPVR_FLAG_AC3_CAP;
		else
			dev->flags &= ~HDPVR_FLAG_AC3_CAP;
	}

	response = dev->usbc_buf+38;
#ifdef HDPVR_DEBUG
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev, "challenge: %8ph\n",
		 response);
#endif
	challenge(response);
#ifdef HDPVR_DEBUG
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev, " response: %8ph\n",
		 response);
#endif

	msleep(100);
	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0xd1, 0x00 | request_type,
			      0x0000, 0x0000,
			      response, 8,
			      10000);
	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "magic request returned %d\n", ret);

	retval = ret != 8;
unlock:
	mutex_unlock(&dev->usbc_mutex);
	return retval;
}