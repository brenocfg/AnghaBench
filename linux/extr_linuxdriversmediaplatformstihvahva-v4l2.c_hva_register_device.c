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
struct hva_dev {int /*<<< orphan*/  m2m_dev; struct video_device* vdev; int /*<<< orphan*/  ip_version; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 char* HVA_NAME ; 
 int /*<<< orphan*/  HVA_PREFIX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hva_fops ; 
 int /*<<< orphan*/  hva_ioctl_ops ; 
 int /*<<< orphan*/  hva_m2m_ops ; 
 struct device* hva_to_dev (struct hva_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct hva_dev*) ; 

__attribute__((used)) static int hva_register_device(struct hva_dev *hva)
{
	int ret;
	struct video_device *vdev;
	struct device *dev;

	if (!hva)
		return -ENODEV;
	dev = hva_to_dev(hva);

	hva->m2m_dev = v4l2_m2m_init(&hva_m2m_ops);
	if (IS_ERR(hva->m2m_dev)) {
		dev_err(dev, "%s failed to initialize v4l2-m2m device\n",
			HVA_PREFIX);
		ret = PTR_ERR(hva->m2m_dev);
		goto err;
	}

	vdev = video_device_alloc();
	if (!vdev) {
		dev_err(dev, "%s failed to allocate video device\n",
			HVA_PREFIX);
		ret = -ENOMEM;
		goto err_m2m_release;
	}

	vdev->fops = &hva_fops;
	vdev->ioctl_ops = &hva_ioctl_ops;
	vdev->release = video_device_release;
	vdev->lock = &hva->lock;
	vdev->vfl_dir = VFL_DIR_M2M;
	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;
	vdev->v4l2_dev = &hva->v4l2_dev;
	snprintf(vdev->name, sizeof(vdev->name), "%s%lx", HVA_NAME,
		 hva->ip_version);

	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		dev_err(dev, "%s failed to register video device\n",
			HVA_PREFIX);
		goto err_vdev_release;
	}

	hva->vdev = vdev;
	video_set_drvdata(vdev, hva);
	return 0;

err_vdev_release:
	video_device_release(vdev);
err_m2m_release:
	v4l2_m2m_release(hva->m2m_dev);
err:
	return ret;
}