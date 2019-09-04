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
struct raremono_device {int /*<<< orphan*/  usbdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct raremono_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *priv,
					struct v4l2_capability *v)
{
	struct raremono_device *radio = video_drvdata(file);

	strlcpy(v->driver, "radio-raremono", sizeof(v->driver));
	strlcpy(v->card, "Thanko's Raremono", sizeof(v->card));
	usb_make_path(radio->usbdev, v->bus_info, sizeof(v->bus_info));
	v->device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;
	v->capabilities = v->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}