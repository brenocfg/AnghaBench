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
struct dvb_frontend {struct stv0288_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct stv0288_state {struct dvb_frontend frontend; int /*<<< orphan*/  errmode; scalar_t__ fec_inner; scalar_t__ symbol_rate; scalar_t__ tuner_frequency; scalar_t__ initialised; struct i2c_adapter* i2c; struct stv0288_config const* config; } ;
struct stv0288_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STATUS_BER ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  kfree (struct stv0288_state*) ; 
 struct stv0288_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stv0288_ops ; 
 int stv0288_readreg (struct stv0288_state*,int) ; 
 int /*<<< orphan*/  stv0288_writeregI (struct stv0288_state*,int,int) ; 

struct dvb_frontend *stv0288_attach(const struct stv0288_config *config,
				    struct i2c_adapter *i2c)
{
	struct stv0288_state *state = NULL;
	int id;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct stv0288_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;
	state->tuner_frequency = 0;
	state->symbol_rate = 0;
	state->fec_inner = 0;
	state->errmode = STATUS_BER;

	stv0288_writeregI(state, 0x41, 0x04);
	msleep(200);
	id = stv0288_readreg(state, 0x00);
	dprintk("stv0288 id %x\n", id);

	/* register 0x00 contains 0x11 for STV0288  */
	if (id != 0x11)
		goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &stv0288_ops,
			sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);

	return NULL;
}