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
typedef  int u16 ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct s5k5baf {int error; int /*<<< orphan*/  req_fiv; struct v4l2_rect crop_source; int /*<<< orphan*/  apply_cfg; int /*<<< orphan*/  sd; int /*<<< orphan*/  compose; struct v4l2_rect crop_sink; } ;

/* Variables and functions */
#define  CFG_ERROR_RANGE 128 
 int EINVAL ; 
 int /*<<< orphan*/  REG_G_INPUTS_CHANGE_REQ ; 
 int /*<<< orphan*/  REG_G_PREVREQ_IN_WIDTH ; 
 int /*<<< orphan*/  REG_G_PREVZOOM_IN_WIDTH ; 
 int /*<<< orphan*/  REG_G_PREV_CFG_BYPASS_CHANGED ; 
 int /*<<< orphan*/  REG_P_OUT_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S5K5BAF_MAX_FR_TIME ; 
 int s5k5baf_clear_error (struct s5k5baf*) ; 
 int s5k5baf_get_cfg_error (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_fiv (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_validate_cfg (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_rescale (struct v4l2_rect*,struct v4l2_rect*,struct v4l2_rect*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5k5baf_synchronize (struct s5k5baf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_write_seq (struct s5k5baf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int s5k5baf_hw_set_crop_rects(struct s5k5baf *state)
{
	struct v4l2_rect *p, r;
	u16 err;
	int ret;

	p = &state->crop_sink;
	s5k5baf_write_seq(state, REG_G_PREVREQ_IN_WIDTH, p->width, p->height,
			  p->left, p->top);

	s5k5baf_rescale(&r, &state->crop_source, &state->crop_sink,
			&state->compose);
	s5k5baf_write_seq(state, REG_G_PREVZOOM_IN_WIDTH, r.width, r.height,
			  r.left, r.top);

	s5k5baf_synchronize(state, 500, REG_G_INPUTS_CHANGE_REQ);
	s5k5baf_synchronize(state, 500, REG_G_PREV_CFG_BYPASS_CHANGED);
	err = s5k5baf_get_cfg_error(state);
	ret = s5k5baf_clear_error(state);
	if (ret < 0)
		return ret;

	switch (err) {
	case 0:
		break;
	case CFG_ERROR_RANGE:
		/* retry crop with frame interval set to max */
		s5k5baf_hw_set_fiv(state, S5K5BAF_MAX_FR_TIME);
		err = s5k5baf_get_cfg_error(state);
		ret = s5k5baf_clear_error(state);
		if (ret < 0)
			return ret;
		if (err) {
			v4l2_err(&state->sd,
				 "crop error on max frame interval: %d\n", err);
			state->error = -EINVAL;
		}
		s5k5baf_hw_set_fiv(state, state->req_fiv);
		s5k5baf_hw_validate_cfg(state);
		break;
	default:
		v4l2_err(&state->sd, "crop error: %d\n", err);
		return -EINVAL;
	}

	if (!state->apply_cfg)
		return 0;

	p = &state->crop_source;
	s5k5baf_write_seq(state, REG_P_OUT_WIDTH(0), p->width, p->height);
	s5k5baf_hw_set_fiv(state, state->req_fiv);
	s5k5baf_hw_validate_cfg(state);

	return s5k5baf_clear_error(state);
}