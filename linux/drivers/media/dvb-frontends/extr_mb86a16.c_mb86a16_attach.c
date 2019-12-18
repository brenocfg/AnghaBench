#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  set_voltage; } ;
struct dvb_frontend {TYPE_1__ ops; struct mb86a16_state* demodulator_priv; } ;
struct mb86a16_state {struct dvb_frontend frontend; struct mb86a16_config const* config; struct i2c_adapter* i2c_adap; } ;
struct mb86a16_config {int /*<<< orphan*/  set_voltage; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mb86a16_state*) ; 
 struct mb86a16_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb86a16_ops ; 
 int /*<<< orphan*/  mb86a16_read (struct mb86a16_state*,int,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend *mb86a16_attach(const struct mb86a16_config *config,
				    struct i2c_adapter *i2c_adap)
{
	u8 dev_id = 0;
	struct mb86a16_state *state = NULL;

	state = kmalloc(sizeof(struct mb86a16_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	state->config = config;
	state->i2c_adap = i2c_adap;

	mb86a16_read(state, 0x7f, &dev_id);
	if (dev_id != 0xfe)
		goto error;

	memcpy(&state->frontend.ops, &mb86a16_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	state->frontend.ops.set_voltage = state->config->set_voltage;

	return &state->frontend;
error:
	kfree(state);
	return NULL;
}