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
struct TYPE_2__ {scalar_t__ disable_i2c_gate_ctrl; } ;
struct zl10353_state {TYPE_1__ config; } ;
struct dvb_frontend {struct zl10353_state* demodulator_priv; } ;

/* Variables and functions */
 int zl10353_single_write (struct dvb_frontend*,int,int) ; 

__attribute__((used)) static int zl10353_i2c_gate_ctrl(struct dvb_frontend* fe, int enable)
{
	struct zl10353_state *state = fe->demodulator_priv;
	u8 val = 0x0a;

	if (state->config.disable_i2c_gate_ctrl) {
		/* No tuner attached to the internal I2C bus */
		/* If set enable I2C bridge, the main I2C bus stopped hardly */
		return 0;
	}

	if (enable)
		val |= 0x10;

	return zl10353_single_write(fe, 0x62, val);
}