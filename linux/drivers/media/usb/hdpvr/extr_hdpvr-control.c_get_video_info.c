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
struct hdpvr_video_info {int valid; int width; int height; int fps; } ;
struct hdpvr_device {int* usbc_buf; int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int MSG_INFO ; 
 int hdpvr_debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int,int /*<<< orphan*/ *,char*,int,int*) ; 

int get_video_info(struct hdpvr_device *dev, struct hdpvr_video_info *vidinf)
{
	int ret;

	vidinf->valid = false;
	mutex_lock(&dev->usbc_mutex);
	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      0x81, 0x80 | 0x38,
			      0x1400, 0x0003,
			      dev->usbc_buf, 5,
			      1000);

#ifdef HDPVR_DEBUG
	if (hdpvr_debug & MSG_INFO)
		v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
			 "get video info returned: %d, %5ph\n", ret,
			 dev->usbc_buf);
#endif
	mutex_unlock(&dev->usbc_mutex);

	if (ret < 0)
		return ret;

	vidinf->width	= dev->usbc_buf[1] << 8 | dev->usbc_buf[0];
	vidinf->height	= dev->usbc_buf[3] << 8 | dev->usbc_buf[2];
	vidinf->fps	= dev->usbc_buf[4];
	vidinf->valid   = vidinf->width && vidinf->height && vidinf->fps;

	return 0;
}