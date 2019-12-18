#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mtk_mdp_dev {TYPE_2__* vdev; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/ * variant; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int device_caps; int /*<<< orphan*/  num; int /*<<< orphan*/  name; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * lock; int /*<<< orphan*/  (* release ) (TYPE_2__*) ;int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 char* MTK_MDP_MODULE_NAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mtk_mdp_default_variant ; 
 int /*<<< orphan*/  mtk_mdp_m2m_fops ; 
 int /*<<< orphan*/  mtk_mdp_m2m_ioctl_ops ; 
 int /*<<< orphan*/  mtk_mdp_m2m_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 TYPE_2__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_2__*) ; 
 int video_register_device (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_2__*,struct mtk_mdp_dev*) ; 

int mtk_mdp_register_m2m_device(struct mtk_mdp_dev *mdp)
{
	struct device *dev = &mdp->pdev->dev;
	int ret;

	mdp->variant = &mtk_mdp_default_variant;
	mdp->vdev = video_device_alloc();
	if (!mdp->vdev) {
		dev_err(dev, "failed to allocate video device\n");
		ret = -ENOMEM;
		goto err_video_alloc;
	}
	mdp->vdev->device_caps = V4L2_CAP_VIDEO_M2M_MPLANE | V4L2_CAP_STREAMING;
	mdp->vdev->fops = &mtk_mdp_m2m_fops;
	mdp->vdev->ioctl_ops = &mtk_mdp_m2m_ioctl_ops;
	mdp->vdev->release = video_device_release;
	mdp->vdev->lock = &mdp->lock;
	mdp->vdev->vfl_dir = VFL_DIR_M2M;
	mdp->vdev->v4l2_dev = &mdp->v4l2_dev;
	snprintf(mdp->vdev->name, sizeof(mdp->vdev->name), "%s:m2m",
		 MTK_MDP_MODULE_NAME);
	video_set_drvdata(mdp->vdev, mdp);

	mdp->m2m_dev = v4l2_m2m_init(&mtk_mdp_m2m_ops);
	if (IS_ERR(mdp->m2m_dev)) {
		dev_err(dev, "failed to initialize v4l2-m2m device\n");
		ret = PTR_ERR(mdp->m2m_dev);
		goto err_m2m_init;
	}

	ret = video_register_device(mdp->vdev, VFL_TYPE_GRABBER, 2);
	if (ret) {
		dev_err(dev, "failed to register video device\n");
		goto err_vdev_register;
	}

	v4l2_info(&mdp->v4l2_dev, "driver registered as /dev/video%d",
		  mdp->vdev->num);
	return 0;

err_vdev_register:
	v4l2_m2m_release(mdp->m2m_dev);
err_m2m_init:
	video_device_release(mdp->vdev);
err_video_alloc:

	return ret;
}