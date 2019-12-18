#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {scalar_t__ index; scalar_t__ pad; scalar_t__ code; void* min_height; void* max_height; void* max_width; void* min_width; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {scalar_t__ code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_FIXED ; 
 scalar_t__ PAD_CIS ; 
 void* S5K5BAF_CIS_HEIGHT ; 
 void* S5K5BAF_CIS_WIDTH ; 
 void* S5K5BAF_WIN_HEIGHT_MIN ; 
 void* S5K5BAF_WIN_WIDTH_MIN ; 
 TYPE_1__* s5k5baf_formats ; 

__attribute__((used)) static int s5k5baf_enum_frame_size(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	int i;

	if (fse->index > 0)
		return -EINVAL;

	if (fse->pad == PAD_CIS) {
		fse->code = MEDIA_BUS_FMT_FIXED;
		fse->min_width = S5K5BAF_CIS_WIDTH;
		fse->max_width = S5K5BAF_CIS_WIDTH;
		fse->min_height = S5K5BAF_CIS_HEIGHT;
		fse->max_height = S5K5BAF_CIS_HEIGHT;
		return 0;
	}

	i = ARRAY_SIZE(s5k5baf_formats);
	while (--i)
		if (fse->code == s5k5baf_formats[i].code)
			break;
	fse->code = s5k5baf_formats[i].code;
	fse->min_width = S5K5BAF_WIN_WIDTH_MIN;
	fse->max_width = S5K5BAF_CIS_WIDTH;
	fse->max_height = S5K5BAF_WIN_HEIGHT_MIN;
	fse->min_height = S5K5BAF_CIS_HEIGHT;

	return 0;
}