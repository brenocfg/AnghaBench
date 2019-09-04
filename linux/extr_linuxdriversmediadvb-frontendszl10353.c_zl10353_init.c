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
typedef  int /*<<< orphan*/  zl10353_reset_attach ;
typedef  int u8 ;
struct TYPE_2__ {int clock_ctl_1; int pll_0; scalar_t__ parallel_ts; } ;
struct zl10353_state {TYPE_1__ config; } ;
struct dvb_frontend {struct zl10353_state* demodulator_priv; } ;

/* Variables and functions */
 scalar_t__ debug_regs ; 
 int /*<<< orphan*/  zl10353_dump_regs (struct dvb_frontend*) ; 
 int zl10353_read_register (struct zl10353_state*,int) ; 
 int /*<<< orphan*/  zl10353_write (struct dvb_frontend*,int*,int) ; 

__attribute__((used)) static int zl10353_init(struct dvb_frontend *fe)
{
	struct zl10353_state *state = fe->demodulator_priv;
	u8 zl10353_reset_attach[6] = { 0x50, 0x03, 0x64, 0x46, 0x15, 0x0F };

	if (debug_regs)
		zl10353_dump_regs(fe);
	if (state->config.parallel_ts)
		zl10353_reset_attach[2] &= ~0x20;
	if (state->config.clock_ctl_1)
		zl10353_reset_attach[3] = state->config.clock_ctl_1;
	if (state->config.pll_0)
		zl10353_reset_attach[4] = state->config.pll_0;

	/* Do a "hard" reset if not already done */
	if (zl10353_read_register(state, 0x50) != zl10353_reset_attach[1] ||
	    zl10353_read_register(state, 0x51) != zl10353_reset_attach[2]) {
		zl10353_write(fe, zl10353_reset_attach,
				   sizeof(zl10353_reset_attach));
		if (debug_regs)
			zl10353_dump_regs(fe);
	}

	return 0;
}