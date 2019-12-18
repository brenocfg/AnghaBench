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
struct v4l2_input {size_t index; int audioset; scalar_t__ std; scalar_t__ tuner; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct go7007 {TYPE_2__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ tvnorms; } ;
struct TYPE_5__ {size_t num_inputs; int flags; int num_aud_inputs; int sensor_flags; TYPE_1__* inputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int GO7007_BOARD_HAS_TUNER ; 
 int GO7007_SENSOR_TV ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* video_devdata (struct file*) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *inp)
{
	struct go7007 *go = video_drvdata(file);

	if (inp->index >= go->board_info->num_inputs)
		return -EINVAL;

	strscpy(inp->name, go->board_info->inputs[inp->index].name,
		sizeof(inp->name));

	/* If this board has a tuner, it will be the first input */
	if ((go->board_info->flags & GO7007_BOARD_HAS_TUNER) &&
			inp->index == 0)
		inp->type = V4L2_INPUT_TYPE_TUNER;
	else
		inp->type = V4L2_INPUT_TYPE_CAMERA;

	if (go->board_info->num_aud_inputs)
		inp->audioset = (1 << go->board_info->num_aud_inputs) - 1;
	else
		inp->audioset = 0;
	inp->tuner = 0;
	if (go->board_info->sensor_flags & GO7007_SENSOR_TV)
		inp->std = video_devdata(file)->tvnorms;
	else
		inp->std = 0;

	return 0;
}