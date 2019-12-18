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
struct video_device {int minor; int device_caps; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; struct v4l2_device* v4l2_dev; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; } ;
struct v4l2_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_dev; struct video_device vfd; } ;
struct fimc_dev {int id; TYPE_1__ m2m; int /*<<< orphan*/  lock; struct v4l2_device* v4l2_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int /*<<< orphan*/  V4L2_FL_QUIRK_INVERTED_CROP ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  fimc_m2m_fops ; 
 int /*<<< orphan*/  fimc_m2m_ioctl_ops ; 
 int /*<<< orphan*/  m2m_ops ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_device*,char*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct fimc_dev*) ; 

int fimc_register_m2m_device(struct fimc_dev *fimc,
			     struct v4l2_device *v4l2_dev)
{
	struct video_device *vfd = &fimc->m2m.vfd;
	int ret;

	fimc->v4l2_dev = v4l2_dev;

	memset(vfd, 0, sizeof(*vfd));
	vfd->fops = &fimc_m2m_fops;
	vfd->ioctl_ops = &fimc_m2m_ioctl_ops;
	vfd->v4l2_dev = v4l2_dev;
	vfd->minor = -1;
	vfd->release = video_device_release_empty;
	vfd->lock = &fimc->lock;
	vfd->vfl_dir = VFL_DIR_M2M;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M_MPLANE;
	set_bit(V4L2_FL_QUIRK_INVERTED_CROP, &vfd->flags);

	snprintf(vfd->name, sizeof(vfd->name), "fimc.%d.m2m", fimc->id);
	video_set_drvdata(vfd, fimc);

	fimc->m2m.m2m_dev = v4l2_m2m_init(&m2m_ops);
	if (IS_ERR(fimc->m2m.m2m_dev)) {
		v4l2_err(v4l2_dev, "failed to initialize v4l2-m2m device\n");
		return PTR_ERR(fimc->m2m.m2m_dev);
	}

	ret = media_entity_pads_init(&vfd->entity, 0, NULL);
	if (ret)
		goto err_me;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, -1);
	if (ret)
		goto err_vd;

	v4l2_info(v4l2_dev, "Registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));
	return 0;

err_vd:
	media_entity_cleanup(&vfd->entity);
err_me:
	v4l2_m2m_release(fimc->m2m.m2m_dev);
	return ret;
}