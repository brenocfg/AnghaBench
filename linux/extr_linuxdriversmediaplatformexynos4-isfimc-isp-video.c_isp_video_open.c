#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* mdev; } ;
struct media_entity {TYPE_5__ graph_obj; int /*<<< orphan*/  use_count; } ;
struct TYPE_7__ {struct media_entity entity; } ;
struct exynos_video_entity {TYPE_2__ vdev; } ;
struct TYPE_6__ {struct exynos_video_entity ve; } ;
struct fimc_isp {int /*<<< orphan*/  video_lock; TYPE_3__* pdev; TYPE_1__ video_capture; } ;
struct file {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  graph_mutex; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int fimc_pipeline_call (struct exynos_video_entity*,int /*<<< orphan*/ ,struct media_entity*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct fimc_isp* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_open(struct file *file)
{
	struct fimc_isp *isp = video_drvdata(file);
	struct exynos_video_entity *ve = &isp->video_capture.ve;
	struct media_entity *me = &ve->vdev.entity;
	int ret;

	if (mutex_lock_interruptible(&isp->video_lock))
		return -ERESTARTSYS;

	ret = v4l2_fh_open(file);
	if (ret < 0)
		goto unlock;

	ret = pm_runtime_get_sync(&isp->pdev->dev);
	if (ret < 0)
		goto rel_fh;

	if (v4l2_fh_is_singular_file(file)) {
		mutex_lock(&me->graph_obj.mdev->graph_mutex);

		ret = fimc_pipeline_call(ve, open, me, true);

		/* Mark the video pipeline as in use. */
		if (ret == 0)
			me->use_count++;

		mutex_unlock(&me->graph_obj.mdev->graph_mutex);
	}
	if (!ret)
		goto unlock;
rel_fh:
	v4l2_fh_release(file);
unlock:
	mutex_unlock(&isp->video_lock);
	return ret;
}