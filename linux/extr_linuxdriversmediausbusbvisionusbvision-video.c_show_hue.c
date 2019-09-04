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
struct video_device {int dummy; } ;
struct usb_usbvision {int /*<<< orphan*/  hdl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct video_device* to_video_device (struct device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 struct usb_usbvision* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static ssize_t show_hue(struct device *cd,
			struct device_attribute *attr, char *buf)
{
	struct video_device *vdev = to_video_device(cd);
	struct usb_usbvision *usbvision = video_get_drvdata(vdev);
	s32 val = v4l2_ctrl_g_ctrl(v4l2_ctrl_find(&usbvision->hdl,
						  V4L2_CID_HUE));

	return sprintf(buf, "%d\n", val);
}