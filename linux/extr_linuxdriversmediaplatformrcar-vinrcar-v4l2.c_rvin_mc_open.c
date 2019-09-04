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
struct rvin_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__ vdev; } ;
struct file {struct rvin_dev* private_data; } ;

/* Variables and functions */
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int v4l2_fh_open (struct file*) ; 
 int v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int) ; 
 struct rvin_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int rvin_mc_open(struct file *file)
{
	struct rvin_dev *vin = video_drvdata(file);
	int ret;

	ret = mutex_lock_interruptible(&vin->lock);
	if (ret)
		return ret;

	ret = pm_runtime_get_sync(vin->dev);
	if (ret < 0)
		goto err_unlock;

	ret = v4l2_pipeline_pm_use(&vin->vdev.entity, 1);
	if (ret < 0)
		goto err_pm;

	file->private_data = vin;

	ret = v4l2_fh_open(file);
	if (ret)
		goto err_v4l2pm;

	mutex_unlock(&vin->lock);

	return 0;
err_v4l2pm:
	v4l2_pipeline_pm_use(&vin->vdev.entity, 0);
err_pm:
	pm_runtime_put(vin->dev);
err_unlock:
	mutex_unlock(&vin->lock);

	return ret;
}