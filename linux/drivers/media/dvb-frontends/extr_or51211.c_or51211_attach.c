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
struct dvb_frontend {struct or51211_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct or51211_state {struct dvb_frontend frontend; scalar_t__ current_frequency; scalar_t__ initialized; struct i2c_adapter* i2c; struct or51211_config const* config; } ;
struct or51211_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct or51211_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  or51211_ops ; 

struct dvb_frontend* or51211_attach(const struct or51211_config* config,
				    struct i2c_adapter* i2c)
{
	struct or51211_state* state = NULL;

	/* Allocate memory for the internal state */
	state = kzalloc(sizeof(struct or51211_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	/* Setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialized = 0;
	state->current_frequency = 0;

	/* Create dvb_frontend */
	memcpy(&state->frontend.ops, &or51211_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;
}