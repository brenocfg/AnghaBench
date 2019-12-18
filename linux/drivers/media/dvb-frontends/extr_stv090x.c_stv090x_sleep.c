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
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {scalar_t__ device; int demod; TYPE_2__* internal; TYPE_1__* config; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  demod_lock; } ;
struct TYPE_3__ {scalar_t__ (* tuner_sleep ) (struct dvb_frontend*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1_PON_FIELD ; 
 int /*<<< orphan*/  ADC2_PON_FIELD ; 
 int /*<<< orphan*/  DISEQC1_PON_FIELD ; 
 int /*<<< orphan*/  DISEQC2_PON_FIELD ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  STANDBY_FIELD ; 
 int /*<<< orphan*/  STOP_CLKADCI1_FIELD ; 
 int /*<<< orphan*/  STOP_CLKADCI2_FIELD ; 
 int /*<<< orphan*/  STOP_CLKFEC_FIELD ; 
 int /*<<< orphan*/  STOP_CLKPKDT1_FIELD ; 
 int /*<<< orphan*/  STOP_CLKPKDT2_FIELD ; 
 int /*<<< orphan*/  STOP_CLKSAMP1_FIELD ; 
 int /*<<< orphan*/  STOP_CLKSAMP2_FIELD ; 
 int /*<<< orphan*/  STOP_CLKTS_FIELD ; 
 int /*<<< orphan*/  STOP_CLKVIT1_FIELD ; 
 int /*<<< orphan*/  STOP_CLKVIT2_FIELD ; 
 scalar_t__ STV0900 ; 
#define  STV090x_DEMODULATOR_0 129 
#define  STV090x_DEMODULATOR_1 128 
 int /*<<< orphan*/  STV090x_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STV090x_STOPCLK1 ; 
 int /*<<< orphan*/  STV090x_STOPCLK2 ; 
 int /*<<< orphan*/  STV090x_SYNTCTRL ; 
 int /*<<< orphan*/  STV090x_TSTTNR1 ; 
 int /*<<< orphan*/  STV090x_TSTTNR2 ; 
 int /*<<< orphan*/  STV090x_TSTTNR3 ; 
 int /*<<< orphan*/  STV090x_TSTTNR4 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dvb_frontend*) ; 
 scalar_t__ stv090x_i2c_gate_ctrl (struct stv090x_state*,int) ; 
 int /*<<< orphan*/  stv090x_read_reg (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stv090x_write_reg (struct stv090x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv090x_sleep(struct dvb_frontend *fe)
{
	struct stv090x_state *state = fe->demodulator_priv;
	u32 reg;
	u8 full_standby = 0;

	if (stv090x_i2c_gate_ctrl(state, 1) < 0)
		goto err;

	if (state->config->tuner_sleep) {
		if (state->config->tuner_sleep(fe) < 0)
			goto err_gateoff;
	}

	if (stv090x_i2c_gate_ctrl(state, 0) < 0)
		goto err;

	dprintk(FE_DEBUG, 1, "Set %s(%d) to sleep",
		state->device == STV0900 ? "STV0900" : "STV0903",
		state->demod);

	mutex_lock(&state->internal->demod_lock);

	switch (state->demod) {
	case STV090x_DEMODULATOR_0:
		/* power off ADC 1 */
		reg = stv090x_read_reg(state, STV090x_TSTTNR1);
		STV090x_SETFIELD(reg, ADC1_PON_FIELD, 0);
		if (stv090x_write_reg(state, STV090x_TSTTNR1, reg) < 0)
			goto err_unlock;
		/* power off DiSEqC 1 */
		reg = stv090x_read_reg(state, STV090x_TSTTNR2);
		STV090x_SETFIELD(reg, DISEQC1_PON_FIELD, 0);
		if (stv090x_write_reg(state, STV090x_TSTTNR2, reg) < 0)
			goto err_unlock;

		/* check whether path 2 is already sleeping, that is when
		   ADC2 is off */
		reg = stv090x_read_reg(state, STV090x_TSTTNR3);
		if (STV090x_GETFIELD(reg, ADC2_PON_FIELD) == 0)
			full_standby = 1;

		/* stop clocks */
		reg = stv090x_read_reg(state, STV090x_STOPCLK1);
		/* packet delineator 1 clock */
		STV090x_SETFIELD(reg, STOP_CLKPKDT1_FIELD, 1);
		/* ADC 1 clock */
		STV090x_SETFIELD(reg, STOP_CLKADCI1_FIELD, 1);
		/* FEC clock is shared between the two paths, only stop it
		   when full standby is possible */
		if (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKFEC_FIELD, 1);
		if (stv090x_write_reg(state, STV090x_STOPCLK1, reg) < 0)
			goto err_unlock;
		reg = stv090x_read_reg(state, STV090x_STOPCLK2);
		/* sampling 1 clock */
		STV090x_SETFIELD(reg, STOP_CLKSAMP1_FIELD, 1);
		/* viterbi 1 clock */
		STV090x_SETFIELD(reg, STOP_CLKVIT1_FIELD, 1);
		/* TS clock is shared between the two paths, only stop it
		   when full standby is possible */
		if (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKTS_FIELD, 1);
		if (stv090x_write_reg(state, STV090x_STOPCLK2, reg) < 0)
			goto err_unlock;
		break;

	case STV090x_DEMODULATOR_1:
		/* power off ADC 2 */
		reg = stv090x_read_reg(state, STV090x_TSTTNR3);
		STV090x_SETFIELD(reg, ADC2_PON_FIELD, 0);
		if (stv090x_write_reg(state, STV090x_TSTTNR3, reg) < 0)
			goto err_unlock;
		/* power off DiSEqC 2 */
		reg = stv090x_read_reg(state, STV090x_TSTTNR4);
		STV090x_SETFIELD(reg, DISEQC2_PON_FIELD, 0);
		if (stv090x_write_reg(state, STV090x_TSTTNR4, reg) < 0)
			goto err_unlock;

		/* check whether path 1 is already sleeping, that is when
		   ADC1 is off */
		reg = stv090x_read_reg(state, STV090x_TSTTNR1);
		if (STV090x_GETFIELD(reg, ADC1_PON_FIELD) == 0)
			full_standby = 1;

		/* stop clocks */
		reg = stv090x_read_reg(state, STV090x_STOPCLK1);
		/* packet delineator 2 clock */
		STV090x_SETFIELD(reg, STOP_CLKPKDT2_FIELD, 1);
		/* ADC 2 clock */
		STV090x_SETFIELD(reg, STOP_CLKADCI2_FIELD, 1);
		/* FEC clock is shared between the two paths, only stop it
		   when full standby is possible */
		if (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKFEC_FIELD, 1);
		if (stv090x_write_reg(state, STV090x_STOPCLK1, reg) < 0)
			goto err_unlock;
		reg = stv090x_read_reg(state, STV090x_STOPCLK2);
		/* sampling 2 clock */
		STV090x_SETFIELD(reg, STOP_CLKSAMP2_FIELD, 1);
		/* viterbi 2 clock */
		STV090x_SETFIELD(reg, STOP_CLKVIT2_FIELD, 1);
		/* TS clock is shared between the two paths, only stop it
		   when full standby is possible */
		if (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKTS_FIELD, 1);
		if (stv090x_write_reg(state, STV090x_STOPCLK2, reg) < 0)
			goto err_unlock;
		break;

	default:
		dprintk(FE_ERROR, 1, "Wrong demodulator!");
		break;
	}

	if (full_standby) {
		/* general power off */
		reg = stv090x_read_reg(state, STV090x_SYNTCTRL);
		STV090x_SETFIELD(reg, STANDBY_FIELD, 0x01);
		if (stv090x_write_reg(state, STV090x_SYNTCTRL, reg) < 0)
			goto err_unlock;
	}

	mutex_unlock(&state->internal->demod_lock);
	return 0;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
	goto err;
err_unlock:
	mutex_unlock(&state->internal->demod_lock);
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}