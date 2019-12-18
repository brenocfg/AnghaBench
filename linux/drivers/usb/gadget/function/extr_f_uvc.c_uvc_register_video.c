#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int device_caps; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * lock; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/ * v4l2_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_9__ {TYPE_1__* config; } ;
struct uvc_device {TYPE_5__ vdev; TYPE_3__ video; int /*<<< orphan*/  v4l2_dev; TYPE_2__ func; } ;
struct usb_composite_dev {TYPE_4__* gadget; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VFL_DIR_TX ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_attr_function_name ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uvc_v4l2_fops ; 
 int /*<<< orphan*/  uvc_v4l2_ioctl_ops ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_5__*,struct uvc_device*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_5__*) ; 

__attribute__((used)) static int
uvc_register_video(struct uvc_device *uvc)
{
	struct usb_composite_dev *cdev = uvc->func.config->cdev;
	int ret;

	/* TODO reference counting. */
	uvc->vdev.v4l2_dev = &uvc->v4l2_dev;
	uvc->vdev.fops = &uvc_v4l2_fops;
	uvc->vdev.ioctl_ops = &uvc_v4l2_ioctl_ops;
	uvc->vdev.release = video_device_release_empty;
	uvc->vdev.vfl_dir = VFL_DIR_TX;
	uvc->vdev.lock = &uvc->video.mutex;
	uvc->vdev.device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;
	strlcpy(uvc->vdev.name, cdev->gadget->name, sizeof(uvc->vdev.name));

	video_set_drvdata(&uvc->vdev, uvc);

	ret = video_register_device(&uvc->vdev, VFL_TYPE_GRABBER, -1);
	if (ret < 0)
		return ret;

	ret = device_create_file(&uvc->vdev.dev, &dev_attr_function_name);
	if (ret < 0) {
		video_unregister_device(&uvc->vdev);
		return ret;
	}

	return 0;
}