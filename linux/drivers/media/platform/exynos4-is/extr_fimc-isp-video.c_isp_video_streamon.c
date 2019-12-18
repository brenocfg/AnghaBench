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
struct media_entity {int dummy; } ;
struct TYPE_4__ {struct media_entity entity; } ;
struct exynos_video_entity {TYPE_2__* pipe; TYPE_1__ vdev; } ;
struct TYPE_6__ {int streaming; struct exynos_video_entity ve; } ;
struct fimc_isp {TYPE_3__ video_capture; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_5__ {int /*<<< orphan*/  mp; } ;

/* Variables and functions */
 int isp_video_pipeline_validate (struct fimc_isp*) ; 
 int media_pipeline_start (struct media_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (struct media_entity*) ; 
 int vb2_ioctl_streamon (struct file*,void*,int) ; 
 struct fimc_isp* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_streamon(struct file *file, void *priv,
				      enum v4l2_buf_type type)
{
	struct fimc_isp *isp = video_drvdata(file);
	struct exynos_video_entity *ve = &isp->video_capture.ve;
	struct media_entity *me = &ve->vdev.entity;
	int ret;

	ret = media_pipeline_start(me, &ve->pipe->mp);
	if (ret < 0)
		return ret;

	ret = isp_video_pipeline_validate(isp);
	if (ret < 0)
		goto p_stop;

	ret = vb2_ioctl_streamon(file, priv, type);
	if (ret < 0)
		goto p_stop;

	isp->video_capture.streaming = 1;
	return 0;
p_stop:
	media_pipeline_stop(me);
	return ret;
}