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
struct venus_inst {int dummy; } ;
struct venus_format {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  step_width; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {TYPE_1__ stepwise; scalar_t__ index; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_STEPWISE ; 
 struct venus_format* find_format (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_height_max (struct venus_inst*) ; 
 int /*<<< orphan*/  frame_height_min (struct venus_inst*) ; 
 int /*<<< orphan*/  frame_height_step (struct venus_inst*) ; 
 int /*<<< orphan*/  frame_width_max (struct venus_inst*) ; 
 int /*<<< orphan*/  frame_width_min (struct venus_inst*) ; 
 int /*<<< orphan*/  frame_width_step (struct venus_inst*) ; 
 struct venus_inst* to_inst (struct file*) ; 

__attribute__((used)) static int venc_enum_framesizes(struct file *file, void *fh,
				struct v4l2_frmsizeenum *fsize)
{
	struct venus_inst *inst = to_inst(file);
	const struct venus_format *fmt;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;

	fmt = find_format(inst, fsize->pixel_format,
			  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	if (!fmt) {
		fmt = find_format(inst, fsize->pixel_format,
				  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
		if (!fmt)
			return -EINVAL;
	}

	if (fsize->index)
		return -EINVAL;

	fsize->stepwise.min_width = frame_width_min(inst);
	fsize->stepwise.max_width = frame_width_max(inst);
	fsize->stepwise.step_width = frame_width_step(inst);
	fsize->stepwise.min_height = frame_height_min(inst);
	fsize->stepwise.max_height = frame_height_max(inst);
	fsize->stepwise.step_height = frame_height_step(inst);

	return 0;
}