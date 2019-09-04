#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {int pad; size_t index; void* code; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 int EINVAL ; 
#define  PREV_PAD_SINK 129 
#define  PREV_PAD_SOURCE 128 
 void** preview_input_fmts ; 
 void** preview_output_fmts ; 

__attribute__((used)) static int preview_enum_mbus_code(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_mbus_code_enum *code)
{
	switch (code->pad) {
	case PREV_PAD_SINK:
		if (code->index >= ARRAY_SIZE(preview_input_fmts))
			return -EINVAL;

		code->code = preview_input_fmts[code->index];
		break;
	case PREV_PAD_SOURCE:
		if (code->index >= ARRAY_SIZE(preview_output_fmts))
			return -EINVAL;

		code->code = preview_output_fmts[code->index];
		break;
	default:
		return -EINVAL;
	}

	return 0;
}