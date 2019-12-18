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
struct video_device {int device_caps; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; } ;
struct coda_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  dev_mutex; TYPE_2__* devtype; struct video_device* vfd; } ;
typedef  enum coda_inst_type { ____Placeholder_coda_inst_type } coda_inst_type ;
struct TYPE_4__ {int num_vdevs; TYPE_1__** vdevs; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CODA_INST_ENCODER ; 
 int EINVAL ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VIDIOC_CROPCAP ; 
 int /*<<< orphan*/  VIDIOC_G_CROP ; 
 int /*<<< orphan*/  VIDIOC_S_CROP ; 
 int /*<<< orphan*/  coda_fops ; 
 int /*<<< orphan*/  coda_ioctl_ops ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_disable_ioctl (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct coda_dev*) ; 

__attribute__((used)) static int coda_register_device(struct coda_dev *dev, int i)
{
	struct video_device *vfd = &dev->vfd[i];
	enum coda_inst_type type;
	int ret;

	if (i >= dev->devtype->num_vdevs)
		return -EINVAL;
	type = dev->devtype->vdevs[i]->type;

	strscpy(vfd->name, dev->devtype->vdevs[i]->name, sizeof(vfd->name));
	vfd->fops	= &coda_fops;
	vfd->ioctl_ops	= &coda_ioctl_ops;
	vfd->release	= video_device_release_empty,
	vfd->lock	= &dev->dev_mutex;
	vfd->v4l2_dev	= &dev->v4l2_dev;
	vfd->vfl_dir	= VFL_DIR_M2M;
	vfd->device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING;
	video_set_drvdata(vfd, dev);

	/* Not applicable, use the selection API instead */
	v4l2_disable_ioctl(vfd, VIDIOC_CROPCAP);
	v4l2_disable_ioctl(vfd, VIDIOC_G_CROP);
	v4l2_disable_ioctl(vfd, VIDIOC_S_CROP);

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, 0);
	if (!ret)
		v4l2_info(&dev->v4l2_dev, "%s registered as %s\n",
			  type == CODA_INST_ENCODER ? "encoder" : "decoder",
			  video_device_node_name(vfd));
	return ret;
}