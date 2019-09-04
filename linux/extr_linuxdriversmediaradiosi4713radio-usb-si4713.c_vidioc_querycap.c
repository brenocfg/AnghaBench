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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct si4713_usb_device {int /*<<< orphan*/  usbdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_MODULATOR ; 
 int V4L2_CAP_RDS_OUTPUT ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct si4713_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *priv,
					struct v4l2_capability *v)
{
	struct si4713_usb_device *radio = video_drvdata(file);

	strlcpy(v->driver, "radio-usb-si4713", sizeof(v->driver));
	strlcpy(v->card, "Si4713 FM Transmitter", sizeof(v->card));
	usb_make_path(radio->usbdev, v->bus_info, sizeof(v->bus_info));
	v->device_caps = V4L2_CAP_MODULATOR | V4L2_CAP_RDS_OUTPUT;
	v->capabilities = v->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}