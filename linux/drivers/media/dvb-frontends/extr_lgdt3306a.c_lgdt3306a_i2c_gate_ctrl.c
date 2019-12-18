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
struct lgdt3306a_state {TYPE_1__* cfg; } ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; } ;
struct TYPE_2__ {int deny_i2c_rptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 int lgdt3306a_set_reg_bit (struct lgdt3306a_state*,int,int,int) ; 

__attribute__((used)) static int lgdt3306a_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct lgdt3306a_state *state = fe->demodulator_priv;

	if (state->cfg->deny_i2c_rptr) {
		dbg_info("deny_i2c_rptr=%d\n", state->cfg->deny_i2c_rptr);
		return 0;
	}
	dbg_info("(%d)\n", enable);

	/* NI2CRPTEN=0x80 */
	return lgdt3306a_set_reg_bit(state, 0x0002, 7, enable ? 0 : 1);
}