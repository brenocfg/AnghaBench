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
struct fimc_lite {int streaming; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_4__* pdev; TYPE_5__ ve; int /*<<< orphan*/  out_path; } ;
struct file {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  graph_mutex; } ;

/* Variables and functions */
 scalar_t__ FIMC_IO_DMA ; 
 int /*<<< orphan*/  ST_FLITE_IN_USE ; 
 int /*<<< orphan*/  ST_FLITE_SUSPENDED ; 
 int /*<<< orphan*/  _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close ; 
 int /*<<< orphan*/  fimc_lite_stop_capture (struct fimc_lite*,int) ; 
 int /*<<< orphan*/  fimc_pipeline_call (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_pipeline_stop (struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 struct fimc_lite* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_lite_release(struct file *file)
{
	struct fimc_lite *fimc = video_drvdata(file);
	struct media_entity *entity = &fimc->ve.vdev.entity;

	mutex_lock(&fimc->lock);

	if (v4l2_fh_is_singular_file(file) &&
	    atomic_read(&fimc->out_path) == FIMC_IO_DMA) {
		if (fimc->streaming) {
			media_pipeline_stop(entity);
			fimc->streaming = false;
		}
		fimc_lite_stop_capture(fimc, false);
		fimc_pipeline_call(&fimc->ve, close);
		clear_bit(ST_FLITE_IN_USE, &fimc->state);

		mutex_lock(&entity->graph_obj.mdev->graph_mutex);
		entity->use_count--;
		mutex_unlock(&entity->graph_obj.mdev->graph_mutex);
	}

	_vb2_fop_release(file, NULL);
	pm_runtime_put(&fimc->pdev->dev);
	clear_bit(ST_FLITE_SUSPENDED, &fimc->state);

	mutex_unlock(&fimc->lock);
	return 0;
}