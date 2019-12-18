#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct media_device* mdev; } ;
struct media_entity {int /*<<< orphan*/  use_count; TYPE_2__ graph_obj; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;
struct TYPE_5__ {struct media_entity entity; } ;
struct TYPE_8__ {TYPE_1__ vdev; } ;
struct fimc_is_video {TYPE_4__ ve; scalar_t__ streaming; } ;
struct fimc_isp {int /*<<< orphan*/  video_lock; TYPE_3__* pdev; struct fimc_is_video video_capture; } ;
struct file {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  close ; 
 int /*<<< orphan*/  fimc_pipeline_call (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_pipeline_stop (struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  vb2_fop_release (struct file*) ; 
 struct fimc_isp* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_release(struct file *file)
{
	struct fimc_isp *isp = video_drvdata(file);
	struct fimc_is_video *ivc = &isp->video_capture;
	struct media_entity *entity = &ivc->ve.vdev.entity;
	struct media_device *mdev = entity->graph_obj.mdev;

	mutex_lock(&isp->video_lock);

	if (v4l2_fh_is_singular_file(file) && ivc->streaming) {
		media_pipeline_stop(entity);
		ivc->streaming = 0;
	}

	vb2_fop_release(file);

	if (v4l2_fh_is_singular_file(file)) {
		fimc_pipeline_call(&ivc->ve, close);

		mutex_lock(&mdev->graph_mutex);
		entity->use_count--;
		mutex_unlock(&mdev->graph_mutex);
	}

	pm_runtime_put(&isp->pdev->dev);
	mutex_unlock(&isp->video_lock);

	return 0;
}