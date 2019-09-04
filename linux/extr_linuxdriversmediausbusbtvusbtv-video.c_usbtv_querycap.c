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
struct usbtv {int /*<<< orphan*/  udev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct usbtv* video_drvdata (struct file*) ; 

__attribute__((used)) static int usbtv_querycap(struct file *file, void *priv,
				struct v4l2_capability *cap)
{
	struct usbtv *dev = video_drvdata(file);

	strlcpy(cap->driver, "usbtv", sizeof(cap->driver));
	strlcpy(cap->card, "usbtv", sizeof(cap->card));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE;
	cap->device_caps |= V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}