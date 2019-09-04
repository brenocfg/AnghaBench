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
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dib7000p_state {struct i2c_adapter dib7090_tuner_adap; } ;

/* Variables and functions */

__attribute__((used)) static struct i2c_adapter *dib7090_get_i2c_tuner(struct dvb_frontend *fe)
{
	struct dib7000p_state *st = fe->demodulator_priv;
	return &st->dib7090_tuner_adap;
}