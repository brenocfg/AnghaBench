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
struct stb0899_state {int /*<<< orphan*/  verbose; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  STB0899_I2CRPT ; 
 int STB0899_I2CTON ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 

int stb0899_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	int i2c_stat;
	struct stb0899_state *state = fe->demodulator_priv;

	i2c_stat = stb0899_read_reg(state, STB0899_I2CRPT);
	if (i2c_stat < 0)
		goto err;

	if (enable) {
		dprintk(state->verbose, FE_DEBUG, 1, "Enabling I2C Repeater ...");
		i2c_stat |=  STB0899_I2CTON;
		if (stb0899_write_reg(state, STB0899_I2CRPT, i2c_stat) < 0)
			goto err;
	} else {
		dprintk(state->verbose, FE_DEBUG, 1, "Disabling I2C Repeater ...");
		i2c_stat &= ~STB0899_I2CTON;
		if (stb0899_write_reg(state, STB0899_I2CRPT, i2c_stat) < 0)
			goto err;
	}
	return 0;
err:
	dprintk(state->verbose, FE_ERROR, 1, "I2C Repeater control failed");
	return -EREMOTEIO;
}