#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxl111sf_reg_ctrl_info {int member_0; int member_1; int member_2; } ;
struct mxl111sf_demod_state {int dummy; } ;
struct TYPE_3__ {int (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct mxl111sf_demod_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int mxl111sf_demod_program_regs (struct mxl111sf_demod_state*,struct mxl111sf_reg_ctrl_info*) ; 
 int mxl1x1sf_demod_reset_irq_status (struct mxl111sf_demod_state*) ; 
 int /*<<< orphan*/  mxl_dbg (char*) ; 
 scalar_t__ mxl_fail (int) ; 
 int stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int mxl111sf_demod_set_frontend(struct dvb_frontend *fe)
{
	struct mxl111sf_demod_state *state = fe->demodulator_priv;
	int ret = 0;

	struct mxl111sf_reg_ctrl_info phy_pll_patch[] = {
		{0x00, 0xff, 0x01}, /* change page to 1 */
		{0x40, 0xff, 0x05},
		{0x40, 0xff, 0x01},
		{0x41, 0xff, 0xca},
		{0x41, 0xff, 0xc0},
		{0x00, 0xff, 0x00}, /* change page to 0 */
		{0,    0,    0}
	};

	mxl_dbg("()");

	if (fe->ops.tuner_ops.set_params) {
		ret = fe->ops.tuner_ops.set_params(fe);
		if (mxl_fail(ret))
			goto fail;
		msleep(50);
	}
	ret = mxl111sf_demod_program_regs(state, phy_pll_patch);
	mxl_fail(ret);
	msleep(50);
	ret = mxl1x1sf_demod_reset_irq_status(state);
	mxl_fail(ret);
	msleep(100);
fail:
	return ret;
}