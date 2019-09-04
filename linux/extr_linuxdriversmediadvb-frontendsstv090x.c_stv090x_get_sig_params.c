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
typedef  void* u32 ;
struct dvb_frontend {int dummy; } ;
struct stv090x_state {scalar_t__ algo; int frequency; int modcod; int pilots; int frame_len; int rolloff; int inversion; int srate; int search_range; TYPE_2__* config; TYPE_1__* internal; int /*<<< orphan*/  delsys; struct dvb_frontend frontend; } ;
typedef  int s32 ;
typedef  enum stv090x_signal_state { ____Placeholder_stv090x_signal_state } stv090x_signal_state ;
struct TYPE_4__ {scalar_t__ (* tuner_get_frequency ) (struct dvb_frontend*,int*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMOD_MODCOD_FIELD ; 
 int /*<<< orphan*/  DEMOD_TYPE_FIELD ; 
 int /*<<< orphan*/  DMDMODCOD ; 
 int /*<<< orphan*/  FECM ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  IQINV_FIELD ; 
 int /*<<< orphan*/  ROLLOFF_STATUS_FIELD ; 
 int /*<<< orphan*/  SFRSTEP ; 
 scalar_t__ STV090x_BLIND_SEARCH ; 
 int STV090x_GETFIELD_Px (void*,int /*<<< orphan*/ ) ; 
 int STV090x_OUTOFRANGE ; 
 int STV090x_RANGEOK ; 
 void* STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TMGOBS ; 
 int /*<<< orphan*/  TMGREG2 ; 
 int abs (int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct dvb_frontend*,int*) ; 
 scalar_t__ stub2 (struct dvb_frontend*,int*) ; 
 int stv090x_car_width (int,int) ; 
 int stv090x_get_car_freq (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_get_std (struct stv090x_state*) ; 
 scalar_t__ stv090x_get_viterbi (struct stv090x_state*) ; 
 scalar_t__ stv090x_i2c_gate_ctrl (struct stv090x_state*,int) ; 

__attribute__((used)) static enum stv090x_signal_state stv090x_get_sig_params(struct stv090x_state *state)
{
	struct dvb_frontend *fe = &state->frontend;

	u8 tmg;
	u32 reg;
	s32 i = 0, offst_freq;

	msleep(5);

	if (state->algo == STV090x_BLIND_SEARCH) {
		tmg = STV090x_READ_DEMOD(state, TMGREG2);
		STV090x_WRITE_DEMOD(state, SFRSTEP, 0x5c);
		while ((i <= 50) && (tmg != 0) && (tmg != 0xff)) {
			tmg = STV090x_READ_DEMOD(state, TMGREG2);
			msleep(5);
			i += 5;
		}
	}
	state->delsys = stv090x_get_std(state);

	if (stv090x_i2c_gate_ctrl(state, 1) < 0)
		goto err;

	if (state->config->tuner_get_frequency) {
		if (state->config->tuner_get_frequency(fe, &state->frequency) < 0)
			goto err_gateoff;
	}

	if (stv090x_i2c_gate_ctrl(state, 0) < 0)
		goto err;

	offst_freq = stv090x_get_car_freq(state, state->internal->mclk) / 1000;
	state->frequency += offst_freq;

	if (stv090x_get_viterbi(state) < 0)
		goto err;

	reg = STV090x_READ_DEMOD(state, DMDMODCOD);
	state->modcod = STV090x_GETFIELD_Px(reg, DEMOD_MODCOD_FIELD);
	state->pilots = STV090x_GETFIELD_Px(reg, DEMOD_TYPE_FIELD) & 0x01;
	state->frame_len = STV090x_GETFIELD_Px(reg, DEMOD_TYPE_FIELD) >> 1;
	reg = STV090x_READ_DEMOD(state, TMGOBS);
	state->rolloff = STV090x_GETFIELD_Px(reg, ROLLOFF_STATUS_FIELD);
	reg = STV090x_READ_DEMOD(state, FECM);
	state->inversion = STV090x_GETFIELD_Px(reg, IQINV_FIELD);

	if ((state->algo == STV090x_BLIND_SEARCH) || (state->srate < 10000000)) {

		if (stv090x_i2c_gate_ctrl(state, 1) < 0)
			goto err;

		if (state->config->tuner_get_frequency) {
			if (state->config->tuner_get_frequency(fe, &state->frequency) < 0)
				goto err_gateoff;
		}

		if (stv090x_i2c_gate_ctrl(state, 0) < 0)
			goto err;

		if (abs(offst_freq) <= ((state->search_range / 2000) + 500))
			return STV090x_RANGEOK;
		else if (abs(offst_freq) <= (stv090x_car_width(state->srate, state->rolloff) / 2000))
			return STV090x_RANGEOK;
	} else {
		if (abs(offst_freq) <= ((state->search_range / 2000) + 500))
			return STV090x_RANGEOK;
	}

	return STV090x_OUTOFRANGE;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}