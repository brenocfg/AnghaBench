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
struct v4l2_subdev_frame_size_enum {scalar_t__ index; scalar_t__ code; void* max_height; void* min_height; void* max_width; void* min_width; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_Y8_1X8 ; 
 void* MT9M032_COLUMN_SIZE_DEF ; 
 void* MT9M032_ROW_SIZE_DEF ; 

__attribute__((used)) static int mt9m032_enum_frame_size(struct v4l2_subdev *subdev,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_frame_size_enum *fse)
{
	if (fse->index != 0 || fse->code != MEDIA_BUS_FMT_Y8_1X8)
		return -EINVAL;

	fse->min_width = MT9M032_COLUMN_SIZE_DEF;
	fse->max_width = MT9M032_COLUMN_SIZE_DEF;
	fse->min_height = MT9M032_ROW_SIZE_DEF;
	fse->max_height = MT9M032_ROW_SIZE_DEF;

	return 0;
}