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
struct v4l2_subdev_frame_size_enum {scalar_t__ code; void* max_height; void* min_height; void* max_width; void* min_width; scalar_t__ index; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 void* BRX_MAX_SIZE ; 
 void* BRX_MIN_SIZE ; 
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_ARGB8888_1X32 ; 
 scalar_t__ MEDIA_BUS_FMT_AYUV8_1X32 ; 

__attribute__((used)) static int brx_enum_frame_size(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_frame_size_enum *fse)
{
	if (fse->index)
		return -EINVAL;

	if (fse->code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
	    fse->code != MEDIA_BUS_FMT_AYUV8_1X32)
		return -EINVAL;

	fse->min_width = BRX_MIN_SIZE;
	fse->max_width = BRX_MAX_SIZE;
	fse->min_height = BRX_MIN_SIZE;
	fse->max_height = BRX_MAX_SIZE;

	return 0;
}