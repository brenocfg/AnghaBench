#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ top; scalar_t__ left; } ;
struct v4l2_subdev_selection {scalar_t__ which; TYPE_1__ r; int /*<<< orphan*/  target; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct s5k5baf {int /*<<< orphan*/  lock; TYPE_1__ crop_source; TYPE_1__ compose; TYPE_1__ crop_sink; } ;
typedef  enum selection_rect { ____Placeholder_selection_rect } selection_rect ;

/* Variables and functions */
 int EINVAL ; 
#define  R_CIS 132 
#define  R_COMPOSE 131 
#define  R_CROP_SINK 130 
#define  R_CROP_SOURCE 129 
#define  R_INVALID 128 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ s5k5baf_cis_rect ; 
 int s5k5baf_get_sel_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s5k5baf_is_bound_target (int /*<<< orphan*/ ) ; 
 struct s5k5baf* to_s5k5baf (struct v4l2_subdev*) ; 
 TYPE_1__* v4l2_subdev_get_try_compose (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 TYPE_1__* v4l2_subdev_get_try_crop (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k5baf_get_selection(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_selection *sel)
{
	enum selection_rect rtype;
	struct s5k5baf *state = to_s5k5baf(sd);

	rtype = s5k5baf_get_sel_rect(sel->pad, sel->target);

	switch (rtype) {
	case R_INVALID:
		return -EINVAL;
	case R_CIS:
		sel->r = s5k5baf_cis_rect;
		return 0;
	default:
		break;
	}

	if (sel->which == V4L2_SUBDEV_FORMAT_TRY) {
		if (rtype == R_COMPOSE)
			sel->r = *v4l2_subdev_get_try_compose(sd, cfg, sel->pad);
		else
			sel->r = *v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		return 0;
	}

	mutex_lock(&state->lock);
	switch (rtype) {
	case R_CROP_SINK:
		sel->r = state->crop_sink;
		break;
	case R_COMPOSE:
		sel->r = state->compose;
		break;
	case R_CROP_SOURCE:
		sel->r = state->crop_source;
		break;
	default:
		break;
	}
	if (s5k5baf_is_bound_target(sel->target)) {
		sel->r.left = 0;
		sel->r.top = 0;
	}
	mutex_unlock(&state->lock);

	return 0;
}