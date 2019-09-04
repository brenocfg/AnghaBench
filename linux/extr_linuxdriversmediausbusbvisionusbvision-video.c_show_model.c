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
struct video_device {int dummy; } ;
struct usb_usbvision {size_t dev_model; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* model_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct video_device* to_video_device (struct device*) ; 
 TYPE_1__* usbvision_device_data ; 
 struct usb_usbvision* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static ssize_t show_model(struct device *cd,
			  struct device_attribute *attr, char *buf)
{
	struct video_device *vdev = to_video_device(cd);
	struct usb_usbvision *usbvision = video_get_drvdata(vdev);
	return sprintf(buf, "%s\n",
		       usbvision_device_data[usbvision->dev_model].model_string);
}