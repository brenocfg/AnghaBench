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
struct v4l2_subdev_frame_size_enum {int index; scalar_t__ code; int min_height; int max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int height; int /*<<< orphan*/  width; } ;
struct tvp5150 {TYPE_1__ rect; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TVP5150_MBUS_FMT ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_enum_frame_size(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_frame_size_enum *fse)
{
	struct tvp5150 *decoder = to_tvp5150(sd);

	if (fse->index >= 8 || fse->code != TVP5150_MBUS_FMT)
		return -EINVAL;

	fse->code = TVP5150_MBUS_FMT;
	fse->min_width = decoder->rect.width;
	fse->max_width = decoder->rect.width;
	fse->min_height = decoder->rect.height / 2;
	fse->max_height = decoder->rect.height / 2;

	return 0;
}