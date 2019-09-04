#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  use_count; } ;
struct TYPE_4__ {TYPE_3__ entity; } ;
struct exynos_video_entity {TYPE_1__ vdev; } ;
struct fimc_vid_cap {int inh_sensor_ctrls; int /*<<< orphan*/  ctx; scalar_t__ user_subdev_api; struct exynos_video_entity ve; } ;
struct fimc_dev {int /*<<< orphan*/  lock; TYPE_2__* pdev; int /*<<< orphan*/  state; struct fimc_vid_cap vid_cap; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ST_CAPT_BUSY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fimc_capture_set_default_format (struct fimc_dev*) ; 
 int fimc_ctrls_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_ctrls_delete (int /*<<< orphan*/ ) ; 
 scalar_t__ fimc_m2m_active (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_md_graph_lock (struct exynos_video_entity*) ; 
 int /*<<< orphan*/  fimc_md_graph_unlock (struct exynos_video_entity*) ; 
 int fimc_pipeline_call (struct exynos_video_entity*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct fimc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_capture_open(struct file *file)
{
	struct fimc_dev *fimc = video_drvdata(file);
	struct fimc_vid_cap *vc = &fimc->vid_cap;
	struct exynos_video_entity *ve = &vc->ve;
	int ret = -EBUSY;

	dbg("pid: %d, state: 0x%lx", task_pid_nr(current), fimc->state);

	mutex_lock(&fimc->lock);

	if (fimc_m2m_active(fimc))
		goto unlock;

	set_bit(ST_CAPT_BUSY, &fimc->state);
	ret = pm_runtime_get_sync(&fimc->pdev->dev);
	if (ret < 0)
		goto unlock;

	ret = v4l2_fh_open(file);
	if (ret) {
		pm_runtime_put_sync(&fimc->pdev->dev);
		goto unlock;
	}

	if (v4l2_fh_is_singular_file(file)) {
		fimc_md_graph_lock(ve);

		ret = fimc_pipeline_call(ve, open, &ve->vdev.entity, true);

		if (ret == 0 && vc->user_subdev_api && vc->inh_sensor_ctrls) {
			/*
			 * Recreate controls of the the video node to drop
			 * any controls inherited from the sensor subdev.
			 */
			fimc_ctrls_delete(vc->ctx);

			ret = fimc_ctrls_create(vc->ctx);
			if (ret == 0)
				vc->inh_sensor_ctrls = false;
		}
		if (ret == 0)
			ve->vdev.entity.use_count++;

		fimc_md_graph_unlock(ve);

		if (ret == 0)
			ret = fimc_capture_set_default_format(fimc);

		if (ret < 0) {
			clear_bit(ST_CAPT_BUSY, &fimc->state);
			pm_runtime_put_sync(&fimc->pdev->dev);
			v4l2_fh_release(file);
		}
	}
unlock:
	mutex_unlock(&fimc->lock);
	return ret;
}