#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {int index; scalar_t__ code; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; int /*<<< orphan*/  max_width; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_4__ {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* ov965x_formats ; 
 TYPE_1__* ov965x_framesizes ; 

__attribute__((used)) static int ov965x_enum_frame_sizes(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_frame_size_enum *fse)
{
	int i = ARRAY_SIZE(ov965x_formats);

	if (fse->index >= ARRAY_SIZE(ov965x_framesizes))
		return -EINVAL;

	while (--i)
		if (fse->code == ov965x_formats[i].code)
			break;

	fse->code = ov965x_formats[i].code;

	fse->min_width  = ov965x_framesizes[fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = ov965x_framesizes[fse->index].height;
	fse->min_height = fse->max_height;

	return 0;
}