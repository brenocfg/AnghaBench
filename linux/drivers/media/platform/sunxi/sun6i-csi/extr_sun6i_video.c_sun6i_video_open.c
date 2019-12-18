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
struct sun6i_video {int /*<<< orphan*/  lock; int /*<<< orphan*/  csi; TYPE_1__ vdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sun6i_csi_set_power (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int) ; 
 struct sun6i_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int sun6i_video_open(struct file *file)
{
	struct sun6i_video *video = video_drvdata(file);
	int ret;

	if (mutex_lock_interruptible(&video->lock))
		return -ERESTARTSYS;

	ret = v4l2_fh_open(file);
	if (ret < 0)
		goto unlock;

	ret = v4l2_pipeline_pm_use(&video->vdev.entity, 1);
	if (ret < 0)
		goto fh_release;

	/* check if already powered */
	if (!v4l2_fh_is_singular_file(file))
		goto unlock;

	ret = sun6i_csi_set_power(video->csi, true);
	if (ret < 0)
		goto fh_release;

	mutex_unlock(&video->lock);
	return 0;

fh_release:
	v4l2_fh_release(file);
unlock:
	mutex_unlock(&video->lock);
	return ret;
}