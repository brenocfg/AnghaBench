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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct exynos_video_entity {int /*<<< orphan*/  pipe; } ;
struct TYPE_2__ {struct exynos_video_entity ve; } ;
struct fimc_dev {TYPE_1__ vid_cap; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IDX_SENSOR ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 struct v4l2_subdev* __fimc_md_get_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_md_graph_lock (struct exynos_video_entity*) ; 
 int /*<<< orphan*/  fimc_md_graph_unlock (struct exynos_video_entity*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fimc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_cap_enum_input(struct file *file, void *priv,
			       struct v4l2_input *i)
{
	struct fimc_dev *fimc = video_drvdata(file);
	struct exynos_video_entity *ve = &fimc->vid_cap.ve;
	struct v4l2_subdev *sd;

	if (i->index != 0)
		return -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	fimc_md_graph_lock(ve);
	sd = __fimc_md_get_subdev(ve->pipe, IDX_SENSOR);
	fimc_md_graph_unlock(ve);

	if (sd)
		strscpy(i->name, sd->name, sizeof(i->name));

	return 0;
}