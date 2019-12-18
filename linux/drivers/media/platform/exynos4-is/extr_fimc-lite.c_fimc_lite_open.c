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
struct TYPE_8__ {TYPE_2__* mdev; } ;
struct media_entity {TYPE_3__ graph_obj; int /*<<< orphan*/  use_count; } ;
struct TYPE_6__ {struct media_entity entity; } ;
struct TYPE_10__ {TYPE_1__ vdev; } ;
struct fimc_lite {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_4__* pdev; TYPE_5__ ve; int /*<<< orphan*/  out_path; } ;
struct file {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  graph_mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ FIMC_IO_DMA ; 
 int /*<<< orphan*/  ST_FLITE_IN_USE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_lite_clear_event_counters (struct fimc_lite*) ; 
 int fimc_pipeline_call (TYPE_5__*,int /*<<< orphan*/ ,struct media_entity*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct fimc_lite* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_lite_open(struct file *file)
{
	struct fimc_lite *fimc = video_drvdata(file);
	struct media_entity *me = &fimc->ve.vdev.entity;
	int ret;

	mutex_lock(&fimc->lock);
	if (atomic_read(&fimc->out_path) != FIMC_IO_DMA) {
		ret = -EBUSY;
		goto unlock;
	}

	set_bit(ST_FLITE_IN_USE, &fimc->state);
	ret = pm_runtime_get_sync(&fimc->pdev->dev);
	if (ret < 0)
		goto unlock;

	ret = v4l2_fh_open(file);
	if (ret < 0)
		goto err_pm;

	if (!v4l2_fh_is_singular_file(file) ||
	    atomic_read(&fimc->out_path) != FIMC_IO_DMA)
		goto unlock;

	mutex_lock(&me->graph_obj.mdev->graph_mutex);

	ret = fimc_pipeline_call(&fimc->ve, open, me, true);

	/* Mark video pipeline ending at this video node as in use. */
	if (ret == 0)
		me->use_count++;

	mutex_unlock(&me->graph_obj.mdev->graph_mutex);

	if (!ret) {
		fimc_lite_clear_event_counters(fimc);
		goto unlock;
	}

	v4l2_fh_release(file);
err_pm:
	pm_runtime_put_sync(&fimc->pdev->dev);
	clear_bit(ST_FLITE_IN_USE, &fimc->state);
unlock:
	mutex_unlock(&fimc->lock);
	return ret;
}