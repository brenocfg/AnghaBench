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
typedef  int u8 ;
struct stv0367ter_state {int guard; int sense; int /*<<< orphan*/  state; scalar_t__ first_lock; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  bw; int /*<<< orphan*/  mode; } ;
struct stv0367_state {scalar_t__ use_i2c_gatectrl; scalar_t__ reinit_on_setfrontend; struct stv0367ter_state* ter_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int transmission_mode; int guard_interval; int bandwidth_hz; int inversion; } ;
struct dvb_frontend {TYPE_2__ ops; struct stv0367_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  FE_TER_CHAN_BW_6M ; 
 int /*<<< orphan*/  FE_TER_CHAN_BW_7M ; 
 int /*<<< orphan*/  FE_TER_CHAN_BW_8M ; 
 int /*<<< orphan*/  FE_TER_HIER_NONE ; 
 int /*<<< orphan*/  FE_TER_LOCKOK ; 
 int /*<<< orphan*/  FE_TER_MODE_2K ; 
 int /*<<< orphan*/  FE_TER_MODE_8K ; 
 int /*<<< orphan*/  FE_TER_NOLOCK ; 
#define  GUARD_INTERVAL_1_16 137 
#define  GUARD_INTERVAL_1_32 136 
#define  GUARD_INTERVAL_1_4 135 
#define  GUARD_INTERVAL_1_8 134 
#define  GUARD_INTERVAL_AUTO 133 
 int INVERSION_AUTO ; 
#define  INVERSION_OFF 132 
#define  INVERSION_ON 131 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stv0367ter_algo (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stv0367ter_init (struct dvb_frontend*) ; 

__attribute__((used)) static int stv0367ter_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct stv0367_state *state = fe->demodulator_priv;
	struct stv0367ter_state *ter_state = state->ter_state;

	/*u8 trials[2]; */
	s8 num_trials, index;
	u8 SenseTrials[] = { INVERSION_ON, INVERSION_OFF };

	if (state->reinit_on_setfrontend)
		stv0367ter_init(fe);

	if (fe->ops.tuner_ops.set_params) {
		if (state->use_i2c_gatectrl && fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.set_params(fe);
		if (state->use_i2c_gatectrl && fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	}

	switch (p->transmission_mode) {
	default:
	case TRANSMISSION_MODE_AUTO:
	case TRANSMISSION_MODE_2K:
		ter_state->mode = FE_TER_MODE_2K;
		break;
/*	case TRANSMISSION_MODE_4K:
		pLook.mode = FE_TER_MODE_4K;
		break;*/
	case TRANSMISSION_MODE_8K:
		ter_state->mode = FE_TER_MODE_8K;
		break;
	}

	switch (p->guard_interval) {
	default:
	case GUARD_INTERVAL_1_32:
	case GUARD_INTERVAL_1_16:
	case GUARD_INTERVAL_1_8:
	case GUARD_INTERVAL_1_4:
		ter_state->guard = p->guard_interval;
		break;
	case GUARD_INTERVAL_AUTO:
		ter_state->guard = GUARD_INTERVAL_1_32;
		break;
	}

	switch (p->bandwidth_hz) {
	case 6000000:
		ter_state->bw = FE_TER_CHAN_BW_6M;
		break;
	case 7000000:
		ter_state->bw = FE_TER_CHAN_BW_7M;
		break;
	case 8000000:
	default:
		ter_state->bw = FE_TER_CHAN_BW_8M;
	}

	ter_state->hierarchy = FE_TER_HIER_NONE;

	switch (p->inversion) {
	case INVERSION_OFF:
	case INVERSION_ON:
		num_trials = 1;
		break;
	default:
		num_trials = 2;
		if (ter_state->first_lock)
			num_trials = 1;
		break;
	}

	ter_state->state = FE_TER_NOLOCK;
	index = 0;

	while (((index) < num_trials) && (ter_state->state != FE_TER_LOCKOK)) {
		if (!ter_state->first_lock) {
			if (p->inversion == INVERSION_AUTO)
				ter_state->sense = SenseTrials[index];

		}
		stv0367ter_algo(fe);

		if ((ter_state->state == FE_TER_LOCKOK) &&
				(p->inversion == INVERSION_AUTO) &&
								(index == 1)) {
			/* invert spectrum sense */
			SenseTrials[index] = SenseTrials[0];
			SenseTrials[(index + 1) % 2] = (SenseTrials[1] + 1) % 2;
		}

		index++;
	}

	return 0;
}