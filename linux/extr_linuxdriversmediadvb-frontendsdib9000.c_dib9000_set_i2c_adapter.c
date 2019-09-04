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
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct TYPE_2__ {struct i2c_adapter* i2c_adap; } ;
struct dib9000_state {TYPE_1__ i2c; } ;

/* Variables and functions */

int dib9000_set_i2c_adapter(struct dvb_frontend *fe, struct i2c_adapter *i2c)
{
	struct dib9000_state *st = fe->demodulator_priv;

	st->i2c.i2c_adap = i2c;
	return 0;
}