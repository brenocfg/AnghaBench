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
struct v4l2_subdev_frame_size_enum {scalar_t__ code; size_t index; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_Y10_1X10 ; 
 TYPE_1__* ov7251_mode_info_data ; 

__attribute__((used)) static int ov7251_enum_frame_size(struct v4l2_subdev *subdev,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	if (fse->code != MEDIA_BUS_FMT_Y10_1X10)
		return -EINVAL;

	if (fse->index >= ARRAY_SIZE(ov7251_mode_info_data))
		return -EINVAL;

	fse->min_width = ov7251_mode_info_data[fse->index].width;
	fse->max_width = ov7251_mode_info_data[fse->index].width;
	fse->min_height = ov7251_mode_info_data[fse->index].height;
	fse->max_height = ov7251_mode_info_data[fse->index].height;

	return 0;
}