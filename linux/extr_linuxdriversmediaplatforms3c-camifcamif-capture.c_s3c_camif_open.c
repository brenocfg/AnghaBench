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
struct file {int dummy; } ;
struct camif_vp {int /*<<< orphan*/  owner; int /*<<< orphan*/  state; int /*<<< orphan*/  id; struct camif_dev* camif; } ;
struct camif_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sensor_set_power (struct camif_dev*,int) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_open(struct file *file)
{
	struct camif_vp *vp = video_drvdata(file);
	struct camif_dev *camif = vp->camif;
	int ret;

	pr_debug("[vp%d] state: %#x,  owner: %p, pid: %d\n", vp->id,
		 vp->state, vp->owner, task_pid_nr(current));

	if (mutex_lock_interruptible(&camif->lock))
		return -ERESTARTSYS;

	ret = v4l2_fh_open(file);
	if (ret < 0)
		goto unlock;

	ret = pm_runtime_get_sync(camif->dev);
	if (ret < 0)
		goto err_pm;

	ret = sensor_set_power(camif, 1);
	if (!ret)
		goto unlock;

	pm_runtime_put(camif->dev);
err_pm:
	v4l2_fh_release(file);
unlock:
	mutex_unlock(&camif->lock);
	return ret;
}