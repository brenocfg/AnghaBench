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
struct v4l2_mbus_framefmt {int field; } ;
struct v4l2_subdev_format {scalar_t__ which; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct adv7180_state {int field; TYPE_1__* chip_info; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ADV7180_FLAG_I2P ; 
 int V4L2_FIELD_ALTERNATE ; 
#define  V4L2_FIELD_NONE 128 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int adv7180_mbus_fmt (struct v4l2_subdev*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  adv7180_set_field_mode (struct adv7180_state*) ; 
 int /*<<< orphan*/  adv7180_set_power (struct adv7180_state*,int) ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7180_set_pad_format(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_format *format)
{
	struct adv7180_state *state = to_state(sd);
	struct v4l2_mbus_framefmt *framefmt;
	int ret;

	switch (format->format.field) {
	case V4L2_FIELD_NONE:
		if (state->chip_info->flags & ADV7180_FLAG_I2P)
			break;
		/* fall through */
	default:
		format->format.field = V4L2_FIELD_ALTERNATE;
		break;
	}

	ret = adv7180_mbus_fmt(sd,  &format->format);

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		if (state->field != format->format.field) {
			state->field = format->format.field;
			adv7180_set_power(state, false);
			adv7180_set_field_mode(state);
			adv7180_set_power(state, true);
		}
	} else {
		framefmt = v4l2_subdev_get_try_format(sd, cfg, 0);
		*framefmt = format->format;
	}

	return ret;
}