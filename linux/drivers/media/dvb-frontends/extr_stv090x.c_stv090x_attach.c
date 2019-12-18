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
struct dvb_frontend {struct stv090x_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct stv090x_state {int demod; struct dvb_frontend frontend; int /*<<< orphan*/  rolloff; int /*<<< orphan*/  device; int /*<<< orphan*/  demod_mode; struct i2c_adapter* i2c; struct stv090x_config* config; int /*<<< orphan*/ * verbose; } ;
struct stv090x_config {int /*<<< orphan*/  device; int /*<<< orphan*/  demod_mode; } ;
struct i2c_adapter {int dummy; } ;
typedef  enum stv090x_demodulator { ____Placeholder_stv090x_demodulator } stv090x_demodulator ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STV090x_RO_35 ; 
 int /*<<< orphan*/  kfree (struct stv090x_state*) ; 
 struct stv090x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_ops ; 
 int stv090x_setup_compound (struct stv090x_state*) ; 
 int /*<<< orphan*/  verbose ; 

struct dvb_frontend *stv090x_attach(struct stv090x_config *config,
				    struct i2c_adapter *i2c,
				    enum stv090x_demodulator demod)
{
	int ret = 0;
	struct stv090x_state *state = NULL;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		goto error;

	state->verbose				= &verbose;
	state->config				= config;
	state->i2c				= i2c;
	state->frontend.ops			= stv090x_ops;
	state->frontend.demodulator_priv	= state;
	state->demod				= demod;
						/* Single or Dual mode */
	state->demod_mode			= config->demod_mode;
	state->device				= config->device;
						/* default */
	state->rolloff				= STV090x_RO_35;

	ret = stv090x_setup_compound(state);
	if (ret)
		goto error;

	return &state->frontend;

error:
	kfree(state);
	return NULL;
}