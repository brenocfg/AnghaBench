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
typedef  int u16 ;
struct stv {int started; int demod_timeout; int fec_timeout; int demod_bits; int search_range; scalar_t__ demod_lock_time; scalar_t__ regoff; TYPE_1__* base; scalar_t__ nr; int /*<<< orphan*/  receive_mode; } ;
struct dtv_frontend_properties {int symbol_rate; } ;
typedef  int s32 ;
struct TYPE_2__ {int mclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FEC_NONE ; 
 int /*<<< orphan*/  RCVMODE_NONE ; 
 scalar_t__ RSTV0910_P2_ACLC2S216A ; 
 scalar_t__ RSTV0910_P2_ACLC2S232A ; 
 scalar_t__ RSTV0910_P2_ACLC2S28 ; 
 scalar_t__ RSTV0910_P2_ACLC2S2Q ; 
 scalar_t__ RSTV0910_P2_BCLC2S216A ; 
 scalar_t__ RSTV0910_P2_BCLC2S232A ; 
 scalar_t__ RSTV0910_P2_BCLC2S28 ; 
 scalar_t__ RSTV0910_P2_BCLC2S2Q ; 
 scalar_t__ RSTV0910_P2_CARCFG ; 
 scalar_t__ RSTV0910_P2_CARFREQ ; 
 scalar_t__ RSTV0910_P2_CARHDR ; 
 scalar_t__ RSTV0910_P2_CFRINIT0 ; 
 scalar_t__ RSTV0910_P2_CFRINIT1 ; 
 scalar_t__ RSTV0910_P2_CFRLOW0 ; 
 scalar_t__ RSTV0910_P2_CFRLOW1 ; 
 scalar_t__ RSTV0910_P2_CFRUP0 ; 
 scalar_t__ RSTV0910_P2_CFRUP1 ; 
 scalar_t__ RSTV0910_P2_DEMOD ; 
 scalar_t__ RSTV0910_P2_DMDCFGMD ; 
 scalar_t__ RSTV0910_P2_DMDISTATE ; 
 scalar_t__ RSTV0910_P2_FECM ; 
 scalar_t__ RSTV0910_P2_PRVIT ; 
 scalar_t__ RSTV0910_P2_SFRINIT0 ; 
 scalar_t__ RSTV0910_P2_SFRINIT1 ; 
 scalar_t__ RSTV0910_TSTRES0 ; 
 int /*<<< orphan*/  RSTV0910_TSTTSRS ; 
 scalar_t__ TUNING_DELAY ; 
 int /*<<< orphan*/  enable_puncture_rate (struct stv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_search_param (struct stv*,struct dtv_frontend_properties*) ; 
 int muldiv32 (int,int,int) ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,int*) ; 
 int /*<<< orphan*/  set_vth_default (struct stv*) ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_shared_reg (struct stv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int start(struct stv *state, struct dtv_frontend_properties *p)
{
	s32 freq;
	u8  reg_dmdcfgmd;
	u16 symb;

	if (p->symbol_rate < 100000 || p->symbol_rate > 70000000)
		return -EINVAL;

	state->receive_mode = RCVMODE_NONE;
	state->demod_lock_time = 0;

	/* Demod Stop */
	if (state->started)
		write_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x5C);

	init_search_param(state, p);

	if (p->symbol_rate <= 1000000) { /* SR <=1Msps */
		state->demod_timeout = 3000;
		state->fec_timeout = 2000;
	} else if (p->symbol_rate <= 2000000) { /* 1Msps < SR <=2Msps */
		state->demod_timeout = 2500;
		state->fec_timeout = 1300;
	} else if (p->symbol_rate <= 5000000) { /* 2Msps< SR <=5Msps */
		state->demod_timeout = 1000;
		state->fec_timeout = 650;
	} else if (p->symbol_rate <= 10000000) { /* 5Msps< SR <=10Msps */
		state->demod_timeout = 700;
		state->fec_timeout = 350;
	} else if (p->symbol_rate < 20000000) { /* 10Msps< SR <=20Msps */
		state->demod_timeout = 400;
		state->fec_timeout = 200;
	} else { /* SR >=20Msps */
		state->demod_timeout = 300;
		state->fec_timeout = 200;
	}

	/* Set the Init Symbol rate */
	symb = muldiv32(p->symbol_rate, 65536, state->base->mclk);
	write_reg(state, RSTV0910_P2_SFRINIT1 + state->regoff,
		  ((symb >> 8) & 0x7F));
	write_reg(state, RSTV0910_P2_SFRINIT0 + state->regoff, (symb & 0xFF));

	state->demod_bits |= 0x80;
	write_reg(state, RSTV0910_P2_DEMOD + state->regoff, state->demod_bits);

	/* FE_STV0910_SetSearchStandard */
	read_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff, &reg_dmdcfgmd);
	write_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff,
		  reg_dmdcfgmd |= 0xC0);

	write_shared_reg(state,
			 RSTV0910_TSTTSRS, state->nr ? 0x02 : 0x01, 0x00);

	/* Disable DSS */
	write_reg(state, RSTV0910_P2_FECM  + state->regoff, 0x00);
	write_reg(state, RSTV0910_P2_PRVIT + state->regoff, 0x2F);

	enable_puncture_rate(state, FEC_NONE);

	/* 8PSK 3/5, 8PSK 2/3 Poff tracking optimization WA */
	write_reg(state, RSTV0910_P2_ACLC2S2Q + state->regoff, 0x0B);
	write_reg(state, RSTV0910_P2_ACLC2S28 + state->regoff, 0x0A);
	write_reg(state, RSTV0910_P2_BCLC2S2Q + state->regoff, 0x84);
	write_reg(state, RSTV0910_P2_BCLC2S28 + state->regoff, 0x84);
	write_reg(state, RSTV0910_P2_CARHDR + state->regoff, 0x1C);
	write_reg(state, RSTV0910_P2_CARFREQ + state->regoff, 0x79);

	write_reg(state, RSTV0910_P2_ACLC2S216A + state->regoff, 0x29);
	write_reg(state, RSTV0910_P2_ACLC2S232A + state->regoff, 0x09);
	write_reg(state, RSTV0910_P2_BCLC2S216A + state->regoff, 0x84);
	write_reg(state, RSTV0910_P2_BCLC2S232A + state->regoff, 0x84);

	/*
	 * Reset CAR3, bug DVBS2->DVBS1 lock
	 * Note: The bit is only pulsed -> no lock on shared register needed
	 */
	write_reg(state, RSTV0910_TSTRES0, state->nr ? 0x04 : 0x08);
	write_reg(state, RSTV0910_TSTRES0, 0);

	set_vth_default(state);
	/* Reset demod */
	write_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x1F);

	write_reg(state, RSTV0910_P2_CARCFG + state->regoff, 0x46);

	if (p->symbol_rate <= 5000000)
		freq = (state->search_range / 2000) + 80;
	else
		freq = (state->search_range / 2000) + 1600;
	freq = (freq << 16) / (state->base->mclk / 1000);

	write_reg(state, RSTV0910_P2_CFRUP1 + state->regoff,
		  (freq >> 8) & 0xff);
	write_reg(state, RSTV0910_P2_CFRUP0 + state->regoff, (freq & 0xff));
	/* CFR Low Setting */
	freq = -freq;
	write_reg(state, RSTV0910_P2_CFRLOW1 + state->regoff,
		  (freq >> 8) & 0xff);
	write_reg(state, RSTV0910_P2_CFRLOW0 + state->regoff, (freq & 0xff));

	/* init the demod frequency offset to 0 */
	write_reg(state, RSTV0910_P2_CFRINIT1 + state->regoff, 0);
	write_reg(state, RSTV0910_P2_CFRINIT0 + state->regoff, 0);

	write_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x1F);
	/* Trigger acq */
	write_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x15);

	state->demod_lock_time += TUNING_DELAY;
	state->started = 1;

	return 0;
}