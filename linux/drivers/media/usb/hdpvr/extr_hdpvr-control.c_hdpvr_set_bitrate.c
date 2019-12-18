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
struct TYPE_2__ {int /*<<< orphan*/  peak_bitrate; int /*<<< orphan*/  bitrate; } ;
struct hdpvr_device {int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/ * usbc_buf; int /*<<< orphan*/  udev; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_BITRATE_VALUE ; 
 int /*<<< orphan*/  CTRL_DEFAULT_INDEX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hdpvr_set_bitrate(struct hdpvr_device *dev)
{
	int ret;

	mutex_lock(&dev->usbc_mutex);
	memset(dev->usbc_buf, 0, 4);
	dev->usbc_buf[0] = dev->options.bitrate;
	dev->usbc_buf[2] = dev->options.peak_bitrate;

	ret = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      0x01, 0x38, CTRL_BITRATE_VALUE,
			      CTRL_DEFAULT_INDEX, dev->usbc_buf, 4, 1000);
	mutex_unlock(&dev->usbc_mutex);

	return ret;
}