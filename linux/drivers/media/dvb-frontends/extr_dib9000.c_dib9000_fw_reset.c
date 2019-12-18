#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct TYPE_4__ {int if_drives; } ;
struct TYPE_5__ {TYPE_1__ cfg; } ;
struct TYPE_6__ {TYPE_2__ d9; } ;
struct dib9000_state {int reg_offs; TYPE_3__ chip; int /*<<< orphan*/  i2c_master; int /*<<< orphan*/  i2c; int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB9000_POWER_ALL ; 
 int /*<<< orphan*/  DIB9000_POWER_INTERFACE_ONLY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dib9000_identify (int /*<<< orphan*/ *) ; 
 int dib9000_read_word (struct dib9000_state*,int) ; 
 int /*<<< orphan*/  dib9000_set_power_mode (struct dib9000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib9000_write_word (struct dib9000_state*,int,int) ; 
 int /*<<< orphan*/  dibx000_reset_i2c_master (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib9000_fw_reset(struct dvb_frontend *fe)
{
	struct dib9000_state *state = fe->demodulator_priv;

	dib9000_write_word(state, 1817, 0x0003);

	dib9000_write_word(state, 1227, 1);
	dib9000_write_word(state, 1227, 0);

	switch ((state->revision = dib9000_identify(&state->i2c))) {
	case 0x4003:
	case 0x4004:
	case 0x4005:
		state->reg_offs = 1;
		break;
	default:
		return -EINVAL;
	}

	/* reset the i2c-master to use the host interface */
	dibx000_reset_i2c_master(&state->i2c_master);

	dib9000_set_power_mode(state, DIB9000_POWER_ALL);

	/* unforce divstr regardless whether i2c enumeration was done or not */
	dib9000_write_word(state, 1794, dib9000_read_word(state, 1794) & ~(1 << 1));
	dib9000_write_word(state, 1796, 0);
	dib9000_write_word(state, 1805, 0x805);

	/* restart all parts */
	dib9000_write_word(state, 898, 0xffff);
	dib9000_write_word(state, 899, 0xffff);
	dib9000_write_word(state, 900, 0x0001);
	dib9000_write_word(state, 901, 0xff19);
	dib9000_write_word(state, 902, 0x003c);

	dib9000_write_word(state, 898, 0);
	dib9000_write_word(state, 899, 0);
	dib9000_write_word(state, 900, 0);
	dib9000_write_word(state, 901, 0);
	dib9000_write_word(state, 902, 0);

	dib9000_write_word(state, 911, state->chip.d9.cfg.if_drives);

	dib9000_set_power_mode(state, DIB9000_POWER_INTERFACE_ONLY);

	return 0;
}