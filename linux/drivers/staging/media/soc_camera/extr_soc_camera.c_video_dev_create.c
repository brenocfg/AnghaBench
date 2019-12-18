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
struct video_device {int /*<<< orphan*/ * lock; int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  name; } ;
struct soc_camera_host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  drv_name; } ;
struct soc_camera_device {struct video_device* vdev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  soc_camera_fops ; 
 int /*<<< orphan*/  soc_camera_ioctl_ops ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 

__attribute__((used)) static int video_dev_create(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct video_device *vdev = video_device_alloc();

	if (!vdev)
		return -ENOMEM;

	strscpy(vdev->name, ici->drv_name, sizeof(vdev->name));

	vdev->v4l2_dev		= &ici->v4l2_dev;
	vdev->fops		= &soc_camera_fops;
	vdev->ioctl_ops		= &soc_camera_ioctl_ops;
	vdev->release		= video_device_release;
	vdev->ctrl_handler	= &icd->ctrl_handler;
	vdev->lock		= &ici->host_lock;

	icd->vdev = vdev;

	return 0;
}