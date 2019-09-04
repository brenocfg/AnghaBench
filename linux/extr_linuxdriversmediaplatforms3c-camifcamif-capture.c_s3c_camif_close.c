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
struct file {scalar_t__ private_data; } ;
struct camif_vp {scalar_t__ owner; int /*<<< orphan*/  vb_queue; int /*<<< orphan*/  state; int /*<<< orphan*/  id; struct camif_dev* camif; } ;
struct camif_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  camif_stop_capture (struct camif_vp*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sensor_set_power (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int v4l2_fh_release (struct file*) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_close(struct file *file)
{
	struct camif_vp *vp = video_drvdata(file);
	struct camif_dev *camif = vp->camif;
	int ret;

	pr_debug("[vp%d] state: %#x, owner: %p, pid: %d\n", vp->id,
		 vp->state, vp->owner, task_pid_nr(current));

	mutex_lock(&camif->lock);

	if (vp->owner == file->private_data) {
		camif_stop_capture(vp);
		vb2_queue_release(&vp->vb_queue);
		vp->owner = NULL;
	}

	sensor_set_power(camif, 0);

	pm_runtime_put(camif->dev);
	ret = v4l2_fh_release(file);

	mutex_unlock(&camif->lock);
	return ret;
}