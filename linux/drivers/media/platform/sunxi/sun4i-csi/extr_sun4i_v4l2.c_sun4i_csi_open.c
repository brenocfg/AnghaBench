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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct sun4i_csi {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__ vdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int v4l2_fh_open (struct file*) ; 
 int v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int) ; 
 struct sun4i_csi* video_drvdata (struct file*) ; 

__attribute__((used)) static int sun4i_csi_open(struct file *file)
{
	struct sun4i_csi *csi = video_drvdata(file);
	int ret;

	ret = mutex_lock_interruptible(&csi->lock);
	if (ret)
		return ret;

	ret = pm_runtime_get_sync(csi->dev);
	if (ret < 0)
		goto err_pm_put;

	ret = v4l2_pipeline_pm_use(&csi->vdev.entity, 1);
	if (ret)
		goto err_pm_put;

	ret = v4l2_fh_open(file);
	if (ret)
		goto err_pipeline_pm_put;

	mutex_unlock(&csi->lock);

	return 0;

err_pipeline_pm_put:
	v4l2_pipeline_pm_use(&csi->vdev.entity, 0);

err_pm_put:
	pm_runtime_put(csi->dev);
	mutex_unlock(&csi->lock);

	return ret;
}