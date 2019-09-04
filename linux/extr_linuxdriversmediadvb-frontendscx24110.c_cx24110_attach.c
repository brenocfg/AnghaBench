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
struct dvb_frontend {struct cx24110_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct cx24110_state {struct dvb_frontend frontend; scalar_t__ lastesn0; scalar_t__ lastbler; scalar_t__ lastber; struct i2c_adapter* i2c; struct cx24110_config const* config; } ;
struct cx24110_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cx24110_ops ; 
 int cx24110_readreg (struct cx24110_state*,int) ; 
 int /*<<< orphan*/  kfree (struct cx24110_state*) ; 
 struct cx24110_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend* cx24110_attach(const struct cx24110_config* config,
				    struct i2c_adapter* i2c)
{
	struct cx24110_state* state = NULL;
	int ret;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct cx24110_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->lastber = 0;
	state->lastbler = 0;
	state->lastesn0 = 0;

	/* check if the demod is there */
	ret = cx24110_readreg(state, 0x00);
	if ((ret != 0x5a) && (ret != 0x69)) goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &cx24110_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}