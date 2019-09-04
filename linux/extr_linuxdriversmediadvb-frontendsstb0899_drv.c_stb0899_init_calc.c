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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct stb0899_internal {int master_clk; int mclk; int agc_gain; int av_frame_coarse; int av_frame_fine; int step_size; scalar_t__ center_freq; int /*<<< orphan*/  rrc_alpha; int /*<<< orphan*/  rolloff; scalar_t__ t_agc2; scalar_t__ t_agc1; } ;
struct stb0899_state {struct stb0899_internal internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_AGC_CNTRL ; 
 int /*<<< orphan*/  IF_GAIN_INIT ; 
 int /*<<< orphan*/  RRC_ALPHA ; 
 int /*<<< orphan*/  STB0899_AGC1REF ; 
 int /*<<< orphan*/  STB0899_BASE_IF_AGC_CNTRL ; 
 int /*<<< orphan*/  STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_OFF0_IF_AGC_CNTRL ; 
 int /*<<< orphan*/  STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stb0899_get_alpha (struct stb0899_state*) ; 
 int stb0899_get_mclk (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_read_regs (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stb0899_write_s2reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stb0899_init_calc(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	int master_clk;
	u8 agc[2];
	u32 reg;

	/* Read registers (in burst mode)	*/
	stb0899_read_regs(state, STB0899_AGC1REF, agc, 2); /* AGC1R and AGC2O	*/

	/* Initial calculations	*/
	master_clk			= stb0899_get_mclk(state);
	internal->t_agc1		= 0;
	internal->t_agc2		= 0;
	internal->master_clk		= master_clk;
	internal->mclk			= master_clk / 65536L;
	internal->rolloff		= stb0899_get_alpha(state);

	/* DVBS2 Initial calculations	*/
	/* Set AGC value to the middle	*/
	internal->agc_gain		= 8154;
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_CNTRL);
	STB0899_SETFIELD_VAL(IF_GAIN_INIT, reg, internal->agc_gain);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_IF_AGC_CNTRL, STB0899_OFF0_IF_AGC_CNTRL, reg);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, RRC_ALPHA);
	internal->rrc_alpha		= STB0899_GETFIELD(RRC_ALPHA, reg);

	internal->center_freq		= 0;
	internal->av_frame_coarse	= 10;
	internal->av_frame_fine		= 20;
	internal->step_size		= 2;
/*
	if ((pParams->SpectralInv == FE_IQ_NORMAL) || (pParams->SpectralInv == FE_IQ_AUTO))
		pParams->IQLocked = 0;
	else
		pParams->IQLocked = 1;
*/
}