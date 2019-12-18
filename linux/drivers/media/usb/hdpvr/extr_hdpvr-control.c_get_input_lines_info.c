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
struct hdpvr_device {int* usbc_buf; int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int MSG_INFO ; 
 int hdpvr_debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int,int /*<<< orphan*/ *,char*,int,int*) ; 

int get_input_lines_info(struct hdpvr_device *dev)
{
	int ret, lines;

	mutex_lock(&dev->usbc_mutex);
	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      0x81, 0x80 | 0x38,
			      0x1800, 0x0003,
			      dev->usbc_buf, 3,
			      1000);

#ifdef HDPVR_DEBUG
	if (hdpvr_debug & MSG_INFO)
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "get input lines info returned: %d, %3ph\n", ret,
			 dev->usbc_buf);
#else
	(void)ret;	/* suppress compiler warning */
#endif
	lines = dev->usbc_buf[1] << 8 | dev->usbc_buf[0];
	mutex_unlock(&dev->usbc_mutex);
	return lines;
}