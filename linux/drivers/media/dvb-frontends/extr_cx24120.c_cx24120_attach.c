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
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct dvb_frontend {struct cx24120_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct cx24120_state {struct dvb_frontend frontend; scalar_t__ cold_init; struct i2c_adapter* i2c; struct cx24120_config const* config; } ;
struct cx24120_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX24120_REG_REVISION ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cx24120_ops ; 
 int cx24120_readreg (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  kfree (struct cx24120_state*) ; 
 struct cx24120_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend *cx24120_attach(const struct cx24120_config *config,
				    struct i2c_adapter *i2c)
{
	struct cx24120_state *state;
	int demod_rev;

	info("Conexant cx24120/cx24118 - DVBS/S2 Satellite demod/tuner\n");
	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state) {
		err("Unable to allocate memory for cx24120_state\n");
		goto error;
	}

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is present and has proper type */
	demod_rev = cx24120_readreg(state, CX24120_REG_REVISION);
	switch (demod_rev) {
	case 0x07:
		info("Demod cx24120 rev. 0x07 detected.\n");
		break;
	case 0x05:
		info("Demod cx24120 rev. 0x05 detected.\n");
		break;
	default:
		err("Unsupported demod revision: 0x%x detected.\n", demod_rev);
		goto error;
	}

	/* create dvb_frontend */
	state->cold_init = 0;
	memcpy(&state->frontend.ops, &cx24120_ops,
	       sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	info("Conexant cx24120/cx24118 attached.\n");
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}