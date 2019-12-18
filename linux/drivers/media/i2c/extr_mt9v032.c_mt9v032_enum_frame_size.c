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
struct v4l2_subdev_frame_size_enum {int index; scalar_t__ code; int min_width; int max_width; int min_height; int max_height; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 int MT9V032_WINDOW_HEIGHT_DEF ; 
 int MT9V032_WINDOW_WIDTH_DEF ; 

__attribute__((used)) static int mt9v032_enum_frame_size(struct v4l2_subdev *subdev,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_frame_size_enum *fse)
{
	if (fse->index >= 3 || fse->code != MEDIA_BUS_FMT_SGRBG10_1X10)
		return -EINVAL;

	fse->min_width = MT9V032_WINDOW_WIDTH_DEF / (1 << fse->index);
	fse->max_width = fse->min_width;
	fse->min_height = MT9V032_WINDOW_HEIGHT_DEF / (1 << fse->index);
	fse->max_height = fse->min_height;

	return 0;
}