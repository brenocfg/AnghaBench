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
struct soc_camera_host {TYPE_2__* ops; int /*<<< orphan*/  host_lock; } ;
struct soc_camera_device {int /*<<< orphan*/  pdev; TYPE_1__* vdev; int /*<<< orphan*/  use_count; struct file* streamer; int /*<<< orphan*/  vb2_vidq; int /*<<< orphan*/  parent; } ;
struct file {struct soc_camera_device* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; scalar_t__ init_videobuf2; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __soc_camera_power_off (struct soc_camera_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_camera_remove_device (struct soc_camera_device*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int soc_camera_close(struct file *file)
{
	struct soc_camera_device *icd = file->private_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);

	mutex_lock(&ici->host_lock);
	if (icd->streamer == file) {
		if (ici->ops->init_videobuf2)
			vb2_queue_release(&icd->vb2_vidq);
		icd->streamer = NULL;
	}
	icd->use_count--;
	if (!icd->use_count) {
		pm_runtime_suspend(&icd->vdev->dev);
		pm_runtime_disable(&icd->vdev->dev);

		__soc_camera_power_off(icd);

		soc_camera_remove_device(icd);
	}

	mutex_unlock(&ici->host_lock);

	module_put(ici->ops->owner);

	dev_dbg(icd->pdev, "camera device close\n");

	return 0;
}