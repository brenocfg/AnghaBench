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
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {struct i2c_adapter tuner_adap; } ;

/* Variables and functions */

struct i2c_adapter *dib9000_get_tuner_interface(struct dvb_frontend *fe)
{
	struct dib9000_state *st = fe->demodulator_priv;
	return &st->tuner_adap;
}