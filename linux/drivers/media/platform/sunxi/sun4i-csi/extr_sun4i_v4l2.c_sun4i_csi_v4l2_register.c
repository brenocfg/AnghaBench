#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int device_caps; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/  name; int /*<<< orphan*/ * queue; int /*<<< orphan*/ * v4l2_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct sun4i_csi {int /*<<< orphan*/  dev; struct video_device vdev; int /*<<< orphan*/  subdev_fmt; TYPE_2__ fmt; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  v4l; } ;
struct TYPE_3__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_DEFAULT_HEIGHT ; 
 int /*<<< orphan*/  CSI_DEFAULT_WIDTH ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  _sun4i_csi_try_fmt (struct sun4i_csi*,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_csi_fops ; 
 TYPE_1__* sun4i_csi_formats ; 
 int /*<<< orphan*/  sun4i_csi_ioctl_ops ; 
 int /*<<< orphan*/  sun4i_csi_pad_fmt_default ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct sun4i_csi*) ; 

int sun4i_csi_v4l2_register(struct sun4i_csi *csi)
{
	struct video_device *vdev = &csi->vdev;
	int ret;

	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_STREAMING;
	vdev->v4l2_dev = &csi->v4l;
	vdev->queue = &csi->queue;
	strscpy(vdev->name, KBUILD_MODNAME, sizeof(vdev->name));
	vdev->release = video_device_release_empty;
	vdev->lock = &csi->lock;

	/* Set a default format */
	csi->fmt.pixelformat = sun4i_csi_formats[0].fourcc,
	csi->fmt.width = CSI_DEFAULT_WIDTH;
	csi->fmt.height = CSI_DEFAULT_HEIGHT;
	_sun4i_csi_try_fmt(csi, &csi->fmt);
	csi->subdev_fmt = sun4i_csi_pad_fmt_default;

	vdev->fops = &sun4i_csi_fops;
	vdev->ioctl_ops = &sun4i_csi_ioctl_ops;
	video_set_drvdata(vdev, csi);

	ret = video_register_device(&csi->vdev, VFL_TYPE_GRABBER, -1);
	if (ret)
		return ret;

	dev_info(csi->dev, "Device registered as %s\n",
		 video_device_node_name(vdev));

	return 0;
}