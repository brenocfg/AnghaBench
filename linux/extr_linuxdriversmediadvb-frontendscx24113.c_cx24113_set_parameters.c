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
typedef  int u8 ;
struct cx24113_state {int icp_mode; int icp_man; int icp_dig; int prescaler_mode; int icp_auto_low; int icp_auto_mlow; int icp_auto_mhi; int icp_auto_hi; scalar_t__ rev; int lna_gain; int rfvga_bias_ctrl; int acp_on; int bs_delay; int vco_shift; int vco_band; int vco_mode; int bs_freqcnt; int bs_rdiv; } ;

/* Variables and functions */
 scalar_t__ REV_CX24113 ; 
 int VCOBANDSEL_6 ; 
 int cx24113_readreg (struct cx24113_state*,int) ; 
 int /*<<< orphan*/  cx24113_writereg (struct cx24113_state*,int,int) ; 

__attribute__((used)) static void cx24113_set_parameters(struct cx24113_state *state)
{
	u8 r;

	r = cx24113_readreg(state, 0x10) & 0x82;
	r |= state->icp_mode;
	r |= state->icp_man << 4;
	r |= state->icp_dig << 2;
	r |= state->prescaler_mode << 5;
	cx24113_writereg(state, 0x10, r);

	r = (state->icp_auto_low  << 0) | (state->icp_auto_mlow << 2)
		| (state->icp_auto_mhi << 4) | (state->icp_auto_hi << 6);
	cx24113_writereg(state, 0x11, r);

	if (state->rev == REV_CX24113) {
		r = cx24113_readreg(state, 0x20) & 0xec;
		r |= state->lna_gain;
		r |= state->rfvga_bias_ctrl << 4;
		cx24113_writereg(state, 0x20, r);
	}

	r = cx24113_readreg(state, 0x12) & 0x03;
	r |= state->acp_on << 2;
	r |= state->bs_delay << 4;
	cx24113_writereg(state, 0x12, r);

	r = cx24113_readreg(state, 0x18) & 0x40;
	r |= state->vco_shift;
	if (state->vco_band == VCOBANDSEL_6)
		r |= (1 << 7);
	else
		r |= (state->vco_band << 1);
	cx24113_writereg(state, 0x18, r);

	r  = cx24113_readreg(state, 0x14) & 0x20;
	r |= (state->vco_mode << 6) | ((state->bs_freqcnt >> 8) & 0x1f);
	cx24113_writereg(state, 0x14, r);
	cx24113_writereg(state, 0x15, (state->bs_freqcnt        & 0xff));

	cx24113_writereg(state, 0x16, (state->bs_rdiv >> 4) & 0xff);
	r = (cx24113_readreg(state, 0x17) & 0x0f) |
		((state->bs_rdiv & 0x0f) << 4);
	cx24113_writereg(state, 0x17, r);
}