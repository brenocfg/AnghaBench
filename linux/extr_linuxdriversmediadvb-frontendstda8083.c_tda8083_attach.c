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
struct dvb_frontend {struct tda8083_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct tda8083_state {struct dvb_frontend frontend; struct i2c_adapter* i2c; struct tda8083_config const* config; } ;
struct tda8083_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tda8083_state*) ; 
 struct tda8083_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tda8083_ops ; 
 int tda8083_readreg (struct tda8083_state*,int) ; 

struct dvb_frontend* tda8083_attach(const struct tda8083_config* config,
				    struct i2c_adapter* i2c)
{
	struct tda8083_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct tda8083_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is there */
	if ((tda8083_readreg(state, 0x00)) != 0x05) goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &tda8083_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}