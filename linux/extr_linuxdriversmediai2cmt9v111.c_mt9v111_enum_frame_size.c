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
struct v4l2_subdev_frame_size_enum {size_t index; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* mt9v111_frame_sizes ; 

__attribute__((used)) static int mt9v111_enum_frame_size(struct v4l2_subdev *subdev,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_frame_size_enum *fse)
{
	if (fse->pad || fse->index >= ARRAY_SIZE(mt9v111_frame_sizes))
		return -EINVAL;

	fse->min_width = mt9v111_frame_sizes[fse->index].width;
	fse->max_width = mt9v111_frame_sizes[fse->index].width;
	fse->min_height = mt9v111_frame_sizes[fse->index].height;
	fse->max_height = mt9v111_frame_sizes[fse->index].height;

	return 0;
}