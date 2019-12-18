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
typedef  int u32 ;
typedef  int u16 ;
struct mxl111sf_tuner_state {int if_freq; TYPE_1__* cfg; } ;
struct TYPE_2__ {int invert_spectrum; int if_freq; } ;

/* Variables and functions */
 int MXL_IF_HI ; 
 int MXL_IF_LO ; 
 int /*<<< orphan*/  V6_TUNER_IF_FCW_BYP_REG ; 
 int /*<<< orphan*/  V6_TUNER_IF_FCW_REG ; 
 int /*<<< orphan*/  V6_TUNER_IF_SEL_REG ; 
 int mxl111sf_tuner_read_reg (struct mxl111sf_tuner_state*,int /*<<< orphan*/ ,int*) ; 
 int mxl111sf_tuner_write_reg (struct mxl111sf_tuner_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxl_dbg (char*,int,int) ; 
 scalar_t__ mxl_fail (int) ; 

__attribute__((used)) static int mxl1x1sf_tuner_set_if_output_freq(struct mxl111sf_tuner_state *state)
{
	int ret;
	u8 ctrl;
#if 0
	u16 iffcw;
	u32 if_freq;
#endif
	mxl_dbg("(IF polarity = %d, IF freq = 0x%02x)",
		state->cfg->invert_spectrum, state->cfg->if_freq);

	/* set IF polarity */
	ctrl = state->cfg->invert_spectrum;

	ctrl |= state->cfg->if_freq;

	ret = mxl111sf_tuner_write_reg(state, V6_TUNER_IF_SEL_REG, ctrl);
	if (mxl_fail(ret))
		goto fail;

#if 0
	if_freq /= 1000000;

	/* do round */
	if_freq += 0.5;

	if (MXL_IF_LO == state->cfg->if_freq) {
		ctrl = 0x08;
		iffcw = (u16)(if_freq / (108 * 4096));
	} else if (MXL_IF_HI == state->cfg->if_freq) {
		ctrl = 0x08;
		iffcw = (u16)(if_freq / (216 * 4096));
	} else {
		ctrl = 0;
		iffcw = 0;
	}

	ctrl |= (iffcw >> 8);
#endif
	ret = mxl111sf_tuner_read_reg(state, V6_TUNER_IF_FCW_BYP_REG, &ctrl);
	if (mxl_fail(ret))
		goto fail;

	ctrl &= 0xf0;
	ctrl |= 0x90;

	ret = mxl111sf_tuner_write_reg(state, V6_TUNER_IF_FCW_BYP_REG, ctrl);
	if (mxl_fail(ret))
		goto fail;

#if 0
	ctrl = iffcw & 0x00ff;
#endif
	ret = mxl111sf_tuner_write_reg(state, V6_TUNER_IF_FCW_REG, ctrl);
	if (mxl_fail(ret))
		goto fail;

	state->if_freq = state->cfg->if_freq;
fail:
	return ret;
}