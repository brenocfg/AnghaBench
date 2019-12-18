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
struct TYPE_4__ {int /*<<< orphan*/  entity; } ;
struct rvin_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; TYPE_2__ vdev; TYPE_1__* info; int /*<<< orphan*/  ctrl_handler; } ;
struct file {struct rvin_dev* private_data; } ;
struct TYPE_3__ {scalar_t__ use_mc; } ;

/* Variables and functions */
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int rvin_power_parallel (struct rvin_dev*,int) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int) ; 
 struct rvin_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int rvin_open(struct file *file)
{
	struct rvin_dev *vin = video_drvdata(file);
	int ret;

	ret = pm_runtime_get_sync(vin->dev);
	if (ret < 0)
		return ret;

	ret = mutex_lock_interruptible(&vin->lock);
	if (ret)
		goto err_pm;

	file->private_data = vin;

	ret = v4l2_fh_open(file);
	if (ret)
		goto err_unlock;

	if (vin->info->use_mc)
		ret = v4l2_pipeline_pm_use(&vin->vdev.entity, 1);
	else if (v4l2_fh_is_singular_file(file))
		ret = rvin_power_parallel(vin, true);

	if (ret < 0)
		goto err_open;

	ret = v4l2_ctrl_handler_setup(&vin->ctrl_handler);
	if (ret)
		goto err_power;

	mutex_unlock(&vin->lock);

	return 0;
err_power:
	if (vin->info->use_mc)
		v4l2_pipeline_pm_use(&vin->vdev.entity, 0);
	else if (v4l2_fh_is_singular_file(file))
		rvin_power_parallel(vin, false);
err_open:
	v4l2_fh_release(file);
err_unlock:
	mutex_unlock(&vin->lock);
err_pm:
	pm_runtime_put(vin->dev);

	return ret;
}