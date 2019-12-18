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
struct stv0367ter_state {scalar_t__ hierarchy; } ;
struct stv0367_state {struct stv0367ter_state* ter_state; } ;
struct dvb_frontend {struct stv0367_state* demodulator_priv; } ;
struct dtv_frontend_properties {void* guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  hierarchy; void* inversion; int /*<<< orphan*/  modulation; scalar_t__ frequency; } ;
typedef  enum stv0367_ter_mode { ____Placeholder_stv0367_ter_mode } stv0367_ter_mode ;

/* Variables and functions */
 int /*<<< orphan*/  F367TER_INV_SPECTR ; 
 int /*<<< orphan*/  F367TER_SYR_GUARD ; 
 int /*<<< orphan*/  F367TER_SYR_MODE ; 
 int /*<<< orphan*/  F367TER_TPS_CONST ; 
 int /*<<< orphan*/  F367TER_TPS_HIERMODE ; 
 int /*<<< orphan*/  F367TER_TPS_HPCODE ; 
 int /*<<< orphan*/  F367TER_TPS_LPCODE ; 
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  FEC_5_6 ; 
 int /*<<< orphan*/  FEC_7_8 ; 
 int /*<<< orphan*/  FEC_AUTO ; 
 scalar_t__ FE_TER_HIER_LOW_PRIO ; 
#define  FE_TER_MODE_2K 129 
#define  FE_TER_MODE_8K 128 
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_AUTO ; 
 scalar_t__ stv0367_get_tuner_freq (struct dvb_frontend*) ; 
 void* stv0367_readbits (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0367ter_get_frontend(struct dvb_frontend *fe,
				   struct dtv_frontend_properties *p)
{
	struct stv0367_state *state = fe->demodulator_priv;
	struct stv0367ter_state *ter_state = state->ter_state;
	enum stv0367_ter_mode mode;
	int constell = 0,/* snr = 0,*/ Data = 0;

	p->frequency = stv0367_get_tuner_freq(fe);
	if ((int)p->frequency < 0)
		p->frequency = -p->frequency;

	constell = stv0367_readbits(state, F367TER_TPS_CONST);
	if (constell == 0)
		p->modulation = QPSK;
	else if (constell == 1)
		p->modulation = QAM_16;
	else
		p->modulation = QAM_64;

	p->inversion = stv0367_readbits(state, F367TER_INV_SPECTR);

	/* Get the Hierarchical mode */
	Data = stv0367_readbits(state, F367TER_TPS_HIERMODE);

	switch (Data) {
	case 0:
		p->hierarchy = HIERARCHY_NONE;
		break;
	case 1:
		p->hierarchy = HIERARCHY_1;
		break;
	case 2:
		p->hierarchy = HIERARCHY_2;
		break;
	case 3:
		p->hierarchy = HIERARCHY_4;
		break;
	default:
		p->hierarchy = HIERARCHY_AUTO;
		break; /* error */
	}

	/* Get the FEC Rate */
	if (ter_state->hierarchy == FE_TER_HIER_LOW_PRIO)
		Data = stv0367_readbits(state, F367TER_TPS_LPCODE);
	else
		Data = stv0367_readbits(state, F367TER_TPS_HPCODE);

	switch (Data) {
	case 0:
		p->code_rate_HP = FEC_1_2;
		break;
	case 1:
		p->code_rate_HP = FEC_2_3;
		break;
	case 2:
		p->code_rate_HP = FEC_3_4;
		break;
	case 3:
		p->code_rate_HP = FEC_5_6;
		break;
	case 4:
		p->code_rate_HP = FEC_7_8;
		break;
	default:
		p->code_rate_HP = FEC_AUTO;
		break; /* error */
	}

	mode = stv0367_readbits(state, F367TER_SYR_MODE);

	switch (mode) {
	case FE_TER_MODE_2K:
		p->transmission_mode = TRANSMISSION_MODE_2K;
		break;
/*	case FE_TER_MODE_4K:
		p->transmission_mode = TRANSMISSION_MODE_4K;
		break;*/
	case FE_TER_MODE_8K:
		p->transmission_mode = TRANSMISSION_MODE_8K;
		break;
	default:
		p->transmission_mode = TRANSMISSION_MODE_AUTO;
	}

	p->guard_interval = stv0367_readbits(state, F367TER_SYR_GUARD);

	return 0;
}