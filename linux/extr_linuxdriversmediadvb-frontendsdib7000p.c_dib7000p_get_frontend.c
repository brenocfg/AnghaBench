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
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dtv_frontend_properties {void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  modulation; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  bandwidth_hz; int /*<<< orphan*/  inversion; } ;
struct dib7000p_state {int /*<<< orphan*/  current_bandwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_HZ (int /*<<< orphan*/ ) ; 
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_5_6 ; 
 void* FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  INVERSION_AUTO ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 

__attribute__((used)) static int dib7000p_get_frontend(struct dvb_frontend *fe,
				 struct dtv_frontend_properties *fep)
{
	struct dib7000p_state *state = fe->demodulator_priv;
	u16 tps = dib7000p_read_word(state, 463);

	fep->inversion = INVERSION_AUTO;

	fep->bandwidth_hz = BANDWIDTH_TO_HZ(state->current_bandwidth);

	switch ((tps >> 8) & 0x3) {
	case 0:
		fep->transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case 1:
		fep->transmission_mode = TRANSMISSION_MODE_8K;
		break;
	/* case 2: fep->transmission_mode = TRANSMISSION_MODE_4K; break; */
	}

	switch (tps & 0x3) {
	case 0:
		fep->guard_interval = GUARD_INTERVAL_1_32;
		break;
	case 1:
		fep->guard_interval = GUARD_INTERVAL_1_16;
		break;
	case 2:
		fep->guard_interval = GUARD_INTERVAL_1_8;
		break;
	case 3:
		fep->guard_interval = GUARD_INTERVAL_1_4;
		break;
	}

	switch ((tps >> 14) & 0x3) {
	case 0:
		fep->modulation = QPSK;
		break;
	case 1:
		fep->modulation = QAM_16;
		break;
	case 2:
	default:
		fep->modulation = QAM_64;
		break;
	}

	/* as long as the frontend_param structure is fixed for hierarchical transmission I refuse to use it */
	/* (tps >> 13) & 0x1 == hrch is used, (tps >> 10) & 0x7 == alpha */

	fep->hierarchy = HIERARCHY_NONE;
	switch ((tps >> 5) & 0x7) {
	case 1:
		fep->code_rate_HP = FEC_1_2;
		break;
	case 2:
		fep->code_rate_HP = FEC_2_3;
		break;
	case 3:
		fep->code_rate_HP = FEC_3_4;
		break;
	case 5:
		fep->code_rate_HP = FEC_5_6;
		break;
	case 7:
	default:
		fep->code_rate_HP = FEC_7_8;
		break;

	}

	switch ((tps >> 2) & 0x7) {
	case 1:
		fep->code_rate_LP = FEC_1_2;
		break;
	case 2:
		fep->code_rate_LP = FEC_2_3;
		break;
	case 3:
		fep->code_rate_LP = FEC_3_4;
		break;
	case 5:
		fep->code_rate_LP = FEC_5_6;
		break;
	case 7:
	default:
		fep->code_rate_LP = FEC_7_8;
		break;
	}

	/* native interleaver: (dib7000p_read_word(state, 464) >>  5) & 0x1 */

	return 0;
}