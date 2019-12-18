#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct v4l2_ctrl {int dummy; } ;
struct TYPE_4__ {struct v4l2_ctrl* exposure; } ;
struct ov965x {int mclk_frequency; unsigned long exp_row_interval; int /*<<< orphan*/  sd; int /*<<< orphan*/  lock; TYPE_3__* frame_size; TYPE_2__* fiv; TYPE_1__ ctrls; } ;
struct TYPE_6__ {unsigned long max_exp_lines; } ;
struct TYPE_5__ {int clkrc_div; } ;

/* Variables and functions */
 int DEF_CLKRC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_ctrl_modify_range (struct v4l2_ctrl*,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ov965x_update_exposure_ctrl(struct ov965x *ov965x)
{
	struct v4l2_ctrl *ctrl = ov965x->ctrls.exposure;
	unsigned long fint, trow;
	int min, max, def;
	u8 clkrc;

	mutex_lock(&ov965x->lock);
	if (WARN_ON(!ctrl || !ov965x->frame_size)) {
		mutex_unlock(&ov965x->lock);
		return;
	}
	clkrc = DEF_CLKRC + ov965x->fiv->clkrc_div;
	/* Calculate internal clock frequency */
	fint = ov965x->mclk_frequency * ((clkrc >> 7) + 1) /
				((2 * ((clkrc & 0x3f) + 1)));
	/* and the row interval (in us). */
	trow = (2 * 1520 * 1000000UL) / fint;
	max = ov965x->frame_size->max_exp_lines * trow;
	ov965x->exp_row_interval = trow;
	mutex_unlock(&ov965x->lock);

	v4l2_dbg(1, debug, &ov965x->sd, "clkrc: %#x, fi: %lu, tr: %lu, %d\n",
		 clkrc, fint, trow, max);

	/* Update exposure time range to match current frame format. */
	min = (trow + 100) / 100;
	max = (max - 100) / 100;
	def = min + (max - min) / 2;

	if (v4l2_ctrl_modify_range(ctrl, min, max, 1, def))
		v4l2_err(&ov965x->sd, "Exposure ctrl range update failed\n");
}