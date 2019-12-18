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
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {scalar_t__ device; int /*<<< orphan*/  rolloff; int /*<<< orphan*/  inversion; int /*<<< orphan*/  demod_mode; TYPE_1__* internal; struct stv090x_config* config; } ;
struct stv090x_config {scalar_t__ (* tuner_init ) (struct dvb_frontend*) ;int clk_mode; scalar_t__ (* tuner_set_mode ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  xtal; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMOD ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  ROLLOFF_CONTROL_FIELD ; 
 scalar_t__ STV0900 ; 
 int /*<<< orphan*/  STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SYNTCTRL ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TNRCFG2 ; 
 int /*<<< orphan*/  TUNER_WAKE ; 
 int /*<<< orphan*/  TUN_IQSWAP_FIELD ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct dvb_frontend*) ; 
 scalar_t__ stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct dvb_frontend*) ; 
 scalar_t__ stv0900_set_tspath (struct stv090x_state*) ; 
 scalar_t__ stv0903_set_tspath (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_get_mclk (struct stv090x_state*) ; 
 scalar_t__ stv090x_i2c_gate_ctrl (struct stv090x_state*,int) ; 
 scalar_t__ stv090x_ldpc_mode (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_set_mclk (struct stv090x_state*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stv090x_wakeup (struct dvb_frontend*) ; 
 scalar_t__ stv090x_write_reg (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv090x_init(struct dvb_frontend *fe)
{
	struct stv090x_state *state = fe->demodulator_priv;
	const struct stv090x_config *config = state->config;
	u32 reg;

	if (state->internal->mclk == 0) {
		/* call tuner init to configure the tuner's clock output
		   divider directly before setting up the master clock of
		   the stv090x. */
		if (stv090x_i2c_gate_ctrl(state, 1) < 0)
			goto err;

		if (config->tuner_init) {
			if (config->tuner_init(fe) < 0)
				goto err_gateoff;
		}

		if (stv090x_i2c_gate_ctrl(state, 0) < 0)
			goto err;

		stv090x_set_mclk(state, 135000000, config->xtal); /* 135 Mhz */
		msleep(5);
		if (stv090x_write_reg(state, STV090x_SYNTCTRL,
				      0x20 | config->clk_mode) < 0)
			goto err;
		stv090x_get_mclk(state);
	}

	if (stv090x_wakeup(fe) < 0) {
		dprintk(FE_ERROR, 1, "Error waking device");
		goto err;
	}

	if (stv090x_ldpc_mode(state, state->demod_mode) < 0)
		goto err;

	reg = STV090x_READ_DEMOD(state, TNRCFG2);
	STV090x_SETFIELD_Px(reg, TUN_IQSWAP_FIELD, state->inversion);
	if (STV090x_WRITE_DEMOD(state, TNRCFG2, reg) < 0)
		goto err;
	reg = STV090x_READ_DEMOD(state, DEMOD);
	STV090x_SETFIELD_Px(reg, ROLLOFF_CONTROL_FIELD, state->rolloff);
	if (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
		goto err;

	if (stv090x_i2c_gate_ctrl(state, 1) < 0)
		goto err;

	if (config->tuner_set_mode) {
		if (config->tuner_set_mode(fe, TUNER_WAKE) < 0)
			goto err_gateoff;
	}

	if (config->tuner_init) {
		if (config->tuner_init(fe) < 0)
			goto err_gateoff;
	}

	if (stv090x_i2c_gate_ctrl(state, 0) < 0)
		goto err;

	if (state->device == STV0900) {
		if (stv0900_set_tspath(state) < 0)
			goto err;
	} else {
		if (stv0903_set_tspath(state) < 0)
			goto err;
	}

	return 0;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}