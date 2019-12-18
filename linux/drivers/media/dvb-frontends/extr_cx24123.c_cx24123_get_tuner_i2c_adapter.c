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
struct dvb_frontend {struct cx24123_state* demodulator_priv; } ;
struct cx24123_state {struct i2c_adapter tuner_i2c_adapter; } ;

/* Variables and functions */

struct i2c_adapter *
	cx24123_get_tuner_i2c_adapter(struct dvb_frontend *fe)
{
	struct cx24123_state *state = fe->demodulator_priv;
	return &state->tuner_i2c_adapter;
}