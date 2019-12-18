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
struct dvb_frontend {struct atbm_state* demodulator_priv; } ;
struct atbm_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_I2C_GATE ; 
 int atbm8830_write_reg (struct atbm_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atbm8830_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct atbm_state *priv = fe->demodulator_priv;

	return atbm8830_write_reg(priv, REG_I2C_GATE, enable ? 1 : 0);
}