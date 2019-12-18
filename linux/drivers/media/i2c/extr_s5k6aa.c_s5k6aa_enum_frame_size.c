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
struct v4l2_subdev_frame_size_enum {scalar_t__ index; scalar_t__ code; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {scalar_t__ code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  S5K6AA_WIN_HEIGHT_MAX ; 
 int /*<<< orphan*/  S5K6AA_WIN_HEIGHT_MIN ; 
 int /*<<< orphan*/  S5K6AA_WIN_WIDTH_MAX ; 
 int /*<<< orphan*/  S5K6AA_WIN_WIDTH_MIN ; 
 TYPE_1__* s5k6aa_formats ; 

__attribute__((used)) static int s5k6aa_enum_frame_size(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	int i = ARRAY_SIZE(s5k6aa_formats);

	if (fse->index > 0)
		return -EINVAL;

	while (--i)
		if (fse->code == s5k6aa_formats[i].code)
			break;

	fse->code = s5k6aa_formats[i].code;
	fse->min_width  = S5K6AA_WIN_WIDTH_MIN;
	fse->max_width  = S5K6AA_WIN_WIDTH_MAX;
	fse->max_height = S5K6AA_WIN_HEIGHT_MIN;
	fse->min_height = S5K6AA_WIN_HEIGHT_MAX;

	return 0;
}