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
struct media_entity {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  entity; } ;
struct TYPE_8__ {struct media_entity entity; } ;
struct TYPE_7__ {TYPE_1__* pipe; TYPE_4__ vdev; } ;
struct fimc_lite {int streaming; TYPE_2__ subdev; int /*<<< orphan*/  sensor; TYPE_3__ ve; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_5__ {int /*<<< orphan*/  mp; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  fimc_find_remote_sensor (int /*<<< orphan*/ *) ; 
 scalar_t__ fimc_lite_active (struct fimc_lite*) ; 
 int fimc_pipeline_validate (struct fimc_lite*) ; 
 int media_pipeline_start (struct media_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (struct media_entity*) ; 
 int vb2_ioctl_streamon (struct file*,void*,int) ; 
 struct fimc_lite* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_lite_streamon(struct file *file, void *priv,
			      enum v4l2_buf_type type)
{
	struct fimc_lite *fimc = video_drvdata(file);
	struct media_entity *entity = &fimc->ve.vdev.entity;
	int ret;

	if (fimc_lite_active(fimc))
		return -EBUSY;

	ret = media_pipeline_start(entity, &fimc->ve.pipe->mp);
	if (ret < 0)
		return ret;

	ret = fimc_pipeline_validate(fimc);
	if (ret < 0)
		goto err_p_stop;

	fimc->sensor = fimc_find_remote_sensor(&fimc->subdev.entity);

	ret = vb2_ioctl_streamon(file, priv, type);
	if (!ret) {
		fimc->streaming = true;
		return ret;
	}

err_p_stop:
	media_pipeline_stop(entity);
	return 0;
}