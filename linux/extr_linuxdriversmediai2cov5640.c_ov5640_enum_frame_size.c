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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {scalar_t__ pad; size_t index; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_width; int /*<<< orphan*/  max_width; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vact; int /*<<< orphan*/  hact; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t OV5640_NUM_MODES ; 
 TYPE_1__** ov5640_mode_data ; 

__attribute__((used)) static int ov5640_enum_frame_size(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	if (fse->pad != 0)
		return -EINVAL;
	if (fse->index >= OV5640_NUM_MODES)
		return -EINVAL;

	fse->min_width =
		ov5640_mode_data[0][fse->index].hact;
	fse->max_width = fse->min_width;
	fse->min_height =
		ov5640_mode_data[0][fse->index].vact;
	fse->max_height = fse->min_height;

	return 0;
}