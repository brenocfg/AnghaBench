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
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct s5k5baf {size_t pixfmt; int /*<<< orphan*/  req_fiv; struct v4l2_rect crop_source; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_p_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_MIPI_INDEX ; 
 int /*<<< orphan*/  FR_RATE_FIXED ; 
 int /*<<< orphan*/  FR_RATE_Q_DYNAMIC ; 
 int PCLK_MAX_FREQ ; 
 int PCLK_MIN_FREQ ; 
 int /*<<< orphan*/  PVI_MASK_MIPI ; 
 int /*<<< orphan*/  REG_P_OUT_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S5K5BAF_MIN_FR_TIME ; 
 TYPE_1__* s5k5baf_formats ; 
 int /*<<< orphan*/  s5k5baf_hw_sync_cfg (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_validate_cfg (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_write_seq (struct s5k5baf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5k5baf_hw_set_config(struct s5k5baf *state)
{
	u16 reg_fmt = s5k5baf_formats[state->pixfmt].reg_p_fmt;
	struct v4l2_rect *r = &state->crop_source;

	s5k5baf_write_seq(state, REG_P_OUT_WIDTH(0),
			  r->width, r->height, reg_fmt,
			  PCLK_MAX_FREQ >> 2, PCLK_MIN_FREQ >> 2,
			  PVI_MASK_MIPI, CLK_MIPI_INDEX,
			  FR_RATE_FIXED, FR_RATE_Q_DYNAMIC,
			  state->req_fiv, S5K5BAF_MIN_FR_TIME);
	s5k5baf_hw_sync_cfg(state);
	s5k5baf_hw_validate_cfg(state);
}