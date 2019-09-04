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
struct usb_usbvision {scalar_t__ isoc_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ ISOC_MODE_COMPRESS ; 
 char* YES_NO (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct video_device* to_video_device (struct device*) ; 
 struct usb_usbvision* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static ssize_t show_compression(struct device *cd,
				struct device_attribute *attr, char *buf)
{
	struct video_device *vdev = to_video_device(cd);
	struct usb_usbvision *usbvision = video_get_drvdata(vdev);
	return sprintf(buf, "%s\n",
		       YES_NO(usbvision->isoc_mode == ISOC_MODE_COMPRESS));
}