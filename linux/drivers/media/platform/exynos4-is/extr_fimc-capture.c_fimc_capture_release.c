#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  use_count; } ;
struct TYPE_7__ {TYPE_3__ entity; } ;
struct TYPE_10__ {TYPE_1__ vdev; } ;
struct fimc_vid_cap {int streaming; TYPE_4__ ve; } ;
struct fimc_dev {int /*<<< orphan*/  lock; TYPE_2__* pdev; int /*<<< orphan*/  state; struct fimc_vid_cap vid_cap; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_CAPT_BUSY ; 
 int /*<<< orphan*/  ST_CAPT_SUSPENDED ; 
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_md_graph_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  fimc_md_graph_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  fimc_pipeline_call (TYPE_4__*,int) ; 
 int /*<<< orphan*/  media_pipeline_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 struct fimc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_capture_release(struct file *file)
{
	struct fimc_dev *fimc = video_drvdata(file);
	struct fimc_vid_cap *vc = &fimc->vid_cap;
	bool close = v4l2_fh_is_singular_file(file);
	int ret;

	dbg("pid: %d, state: 0x%lx", task_pid_nr(current), fimc->state);

	mutex_lock(&fimc->lock);

	if (close && vc->streaming) {
		media_pipeline_stop(&vc->ve.vdev.entity);
		vc->streaming = false;
	}

	ret = _vb2_fop_release(file, NULL);

	if (close) {
		clear_bit(ST_CAPT_BUSY, &fimc->state);
		fimc_pipeline_call(&vc->ve, close);
		clear_bit(ST_CAPT_SUSPENDED, &fimc->state);

		fimc_md_graph_lock(&vc->ve);
		vc->ve.vdev.entity.use_count--;
		fimc_md_graph_unlock(&vc->ve);
	}

	pm_runtime_put_sync(&fimc->pdev->dev);
	mutex_unlock(&fimc->lock);

	return ret;
}