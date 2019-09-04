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
struct stk1160 {int /*<<< orphan*/  udev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct stk1160* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file,
		void *priv, struct v4l2_capability *cap)
{
	struct stk1160 *dev = video_drvdata(file);

	strcpy(cap->driver, "stk1160");
	strcpy(cap->card, "stk1160");
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->device_caps =
		V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_STREAMING |
		V4L2_CAP_READWRITE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}