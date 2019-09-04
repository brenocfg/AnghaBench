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
struct v4l2_subdev_frame_size_enum {int index; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 int OV2680_MODE_MAX ; 
 TYPE_1__* ov2680_mode_data ; 

__attribute__((used)) static int ov2680_enum_frame_size(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	int index = fse->index;

	if (index >= OV2680_MODE_MAX || index < 0)
		return -EINVAL;

	fse->min_width = ov2680_mode_data[index].width;
	fse->min_height = ov2680_mode_data[index].height;
	fse->max_width = ov2680_mode_data[index].width;
	fse->max_height = ov2680_mode_data[index].height;

	return 0;
}