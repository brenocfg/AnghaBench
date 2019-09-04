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
struct dvb_frontend {struct mt352_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct mt352_state {struct dvb_frontend frontend; int /*<<< orphan*/  config; struct i2c_adapter* i2c; } ;
struct mt352_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ID_MT352 ; 
 int /*<<< orphan*/  kfree (struct mt352_state*) ; 
 struct mt352_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mt352_config const*,int) ; 
 struct mt352_config const mt352_ops ; 
 scalar_t__ mt352_read_register (struct mt352_state*,int /*<<< orphan*/ ) ; 

struct dvb_frontend* mt352_attach(const struct mt352_config* config,
				  struct i2c_adapter* i2c)
{
	struct mt352_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct mt352_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->i2c = i2c;
	memcpy(&state->config,config,sizeof(struct mt352_config));

	/* check if the demod is there */
	if (mt352_read_register(state, CHIP_ID) != ID_MT352) goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &mt352_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}