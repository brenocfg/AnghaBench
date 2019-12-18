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
struct dvb_frontend {struct sp887x_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct sp887x_state {struct dvb_frontend frontend; scalar_t__ initialised; struct i2c_adapter* i2c; struct sp887x_config const* config; } ;
struct sp887x_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct sp887x_state*) ; 
 struct sp887x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sp887x_ops ; 
 scalar_t__ sp887x_readreg (struct sp887x_state*,int) ; 

struct dvb_frontend* sp887x_attach(const struct sp887x_config* config,
				   struct i2c_adapter* i2c)
{
	struct sp887x_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct sp887x_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;

	/* check if the demod is there */
	if (sp887x_readreg(state, 0x0200) < 0) goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &sp887x_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}