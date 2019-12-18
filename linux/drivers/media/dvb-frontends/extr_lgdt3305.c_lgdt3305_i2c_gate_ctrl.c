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
struct lgdt3305_state {TYPE_1__* cfg; } ;
struct dvb_frontend {struct lgdt3305_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ deny_i2c_rptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LGDT3305_GEN_CTRL_2 ; 
 int /*<<< orphan*/  lg_dbg (char*,int) ; 
 int lgdt3305_set_reg_bit (struct lgdt3305_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lgdt3305_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct lgdt3305_state *state = fe->demodulator_priv;

	if (state->cfg->deny_i2c_rptr)
		return 0;

	lg_dbg("(%d)\n", enable);

	return lgdt3305_set_reg_bit(state, LGDT3305_GEN_CTRL_2, 5,
				    enable ? 0 : 1);
}