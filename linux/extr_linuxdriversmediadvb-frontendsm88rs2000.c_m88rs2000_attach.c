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
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct m88rs2000_state {struct dvb_frontend frontend; scalar_t__ fec_inner; scalar_t__ symbol_rate; scalar_t__ tuner_frequency; struct i2c_adapter* i2c; struct m88rs2000_config const* config; } ;
struct m88rs2000_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct m88rs2000_state*) ; 
 struct m88rs2000_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m88rs2000_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend *m88rs2000_attach(const struct m88rs2000_config *config,
				    struct i2c_adapter *i2c)
{
	struct m88rs2000_state *state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct m88rs2000_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->tuner_frequency = 0;
	state->symbol_rate = 0;
	state->fec_inner = 0;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &m88rs2000_ops,
			sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);

	return NULL;
}