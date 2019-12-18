#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_input {int /*<<< orphan*/  name; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct file {int dummy; } ;
struct camif_vp {TYPE_2__* camif; } ;
struct TYPE_3__ {struct v4l2_subdev* sd; } ;
struct TYPE_4__ {TYPE_1__ sensor; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_vidioc_enum_input(struct file *file, void *priv,
				       struct v4l2_input *input)
{
	struct camif_vp *vp = video_drvdata(file);
	struct v4l2_subdev *sensor = vp->camif->sensor.sd;

	if (input->index || sensor == NULL)
		return -EINVAL;

	input->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(input->name, sensor->name, sizeof(input->name));
	return 0;
}