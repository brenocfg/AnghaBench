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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mxl111sf_tuner_state {TYPE_1__* cfg; } ;
struct mxl111sf_reg_ctrl_info {int dummy; } ;
struct dvb_frontend {struct mxl111sf_tuner_state* tuner_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ant_hunt ) (struct dvb_frontend*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int MXL_DEV_MODE_MASK ; 
 int /*<<< orphan*/  MXL_MODE_REG ; 
 int MXL_TUNER_MODE ; 
 int /*<<< orphan*/  START_TUNE_REG ; 
 struct mxl111sf_reg_ctrl_info* mxl111sf_calc_phy_tune_regs (int /*<<< orphan*/ ,int) ; 
 int mxl111sf_tuner_program_regs (struct mxl111sf_tuner_state*,struct mxl111sf_reg_ctrl_info*) ; 
 int mxl111sf_tuner_read_reg (struct mxl111sf_tuner_state*,int /*<<< orphan*/ ,int*) ; 
 int mxl111sf_tuner_write_reg (struct mxl111sf_tuner_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxl1x1sf_tuner_set_if_output_freq (struct mxl111sf_tuner_state*) ; 
 int /*<<< orphan*/  mxl1x1sf_tuner_top_master_ctrl (struct mxl111sf_tuner_state*,int) ; 
 int /*<<< orphan*/  mxl_dbg (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int mxl1x1sf_tune_rf(struct dvb_frontend *fe, u32 freq, u8 bw)
{
	struct mxl111sf_tuner_state *state = fe->tuner_priv;
	static struct mxl111sf_reg_ctrl_info *reg_ctrl_array;
	int ret;
	u8 mxl_mode;

	mxl_dbg("(freq = %d, bw = 0x%x)", freq, bw);

	/* stop tune */
	ret = mxl111sf_tuner_write_reg(state, START_TUNE_REG, 0);
	if (mxl_fail(ret))
		goto fail;

	/* check device mode */
	ret = mxl111sf_tuner_read_reg(state, MXL_MODE_REG, &mxl_mode);
	if (mxl_fail(ret))
		goto fail;

	/* Fill out registers for channel tune */
	reg_ctrl_array = mxl111sf_calc_phy_tune_regs(freq, bw);
	if (!reg_ctrl_array)
		return -EINVAL;

	ret = mxl111sf_tuner_program_regs(state, reg_ctrl_array);
	if (mxl_fail(ret))
		goto fail;

	if ((mxl_mode & MXL_DEV_MODE_MASK) == MXL_TUNER_MODE) {
		/* IF tuner mode only */
		mxl1x1sf_tuner_top_master_ctrl(state, 0);
		mxl1x1sf_tuner_top_master_ctrl(state, 1);
		mxl1x1sf_tuner_set_if_output_freq(state);
	}

	ret = mxl111sf_tuner_write_reg(state, START_TUNE_REG, 1);
	if (mxl_fail(ret))
		goto fail;

	if (state->cfg->ant_hunt)
		state->cfg->ant_hunt(fe);
fail:
	return ret;
}