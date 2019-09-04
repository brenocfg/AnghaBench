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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct adv7180_state {int curr_norm; scalar_t__ field; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 int V4L2_STD_525_60 ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7180_mbus_fmt(struct v4l2_subdev *sd,
			    struct v4l2_mbus_framefmt *fmt)
{
	struct adv7180_state *state = to_state(sd);

	fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	fmt->width = 720;
	fmt->height = state->curr_norm & V4L2_STD_525_60 ? 480 : 576;

	if (state->field == V4L2_FIELD_ALTERNATE)
		fmt->height /= 2;

	return 0;
}