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
struct video_device {int device_caps; int /*<<< orphan*/  name; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * lock; int /*<<< orphan*/  (* release ) (struct video_device*) ;int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; } ;
struct delta_dev {int /*<<< orphan*/  m2m_dev; struct video_device* vdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 char* DELTA_FW_VERSION ; 
 char* DELTA_NAME ; 
 int /*<<< orphan*/  DELTA_PREFIX ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  delta_fops ; 
 int /*<<< orphan*/  delta_ioctl_ops ; 
 int /*<<< orphan*/  delta_m2m_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct delta_dev*) ; 

__attribute__((used)) static int delta_register_device(struct delta_dev *delta)
{
	int ret;
	struct video_device *vdev;

	if (!delta)
		return -ENODEV;

	delta->m2m_dev = v4l2_m2m_init(&delta_m2m_ops);
	if (IS_ERR(delta->m2m_dev)) {
		dev_err(delta->dev, "%s failed to initialize v4l2-m2m device\n",
			DELTA_PREFIX);
		ret = PTR_ERR(delta->m2m_dev);
		goto err;
	}

	vdev = video_device_alloc();
	if (!vdev) {
		dev_err(delta->dev, "%s failed to allocate video device\n",
			DELTA_PREFIX);
		ret = -ENOMEM;
		goto err_m2m_release;
	}

	vdev->fops = &delta_fops;
	vdev->ioctl_ops = &delta_ioctl_ops;
	vdev->release = video_device_release;
	vdev->lock = &delta->lock;
	vdev->vfl_dir = VFL_DIR_M2M;
	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;
	vdev->v4l2_dev = &delta->v4l2_dev;
	snprintf(vdev->name, sizeof(vdev->name), "%s-%s",
		 DELTA_NAME, DELTA_FW_VERSION);

	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		dev_err(delta->dev, "%s failed to register video device\n",
			DELTA_PREFIX);
		goto err_vdev_release;
	}

	delta->vdev = vdev;
	video_set_drvdata(vdev, delta);
	return 0;

err_vdev_release:
	video_device_release(vdev);
err_m2m_release:
	v4l2_m2m_release(delta->m2m_dev);
err:
	return ret;
}