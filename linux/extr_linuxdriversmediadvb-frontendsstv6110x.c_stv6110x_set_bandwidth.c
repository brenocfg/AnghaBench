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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct stv6110x_state {int /*<<< orphan*/ * regs; } ;
struct dvb_frontend {struct stv6110x_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL3_CF ; 
 int /*<<< orphan*/  CTRL3_RCCLK_OFF ; 
 int /*<<< orphan*/  STAT1_CALRC_STRT ; 
 size_t STV6110x_CTRL3 ; 
 int /*<<< orphan*/  STV6110x_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV6110x_SETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t STV6110x_STAT1 ; 
 scalar_t__ TRIALS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stv6110x_read_reg (struct stv6110x_state*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stv6110x_write_reg (struct stv6110x_state*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv6110x_set_bandwidth(struct dvb_frontend *fe, u32 bandwidth)
{
	struct stv6110x_state *stv6110x = fe->tuner_priv;
	u32 halfbw;
	u8 i;

	halfbw = bandwidth >> 1;

	if (halfbw > 36000000)
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_CF, 31); /* LPF */
	else if (halfbw < 5000000)
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_CF, 0); /* LPF */
	else
		STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_CF, ((halfbw / 1000000) - 5)); /* LPF */


	STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_RCCLK_OFF, 0x0); /* cal. clk activated */
	STV6110x_SETFIELD(stv6110x->regs[STV6110x_STAT1], STAT1_CALRC_STRT, 0x1); /* LPF auto cal */

	stv6110x_write_reg(stv6110x, STV6110x_CTRL3, stv6110x->regs[STV6110x_CTRL3]);
	stv6110x_write_reg(stv6110x, STV6110x_STAT1, stv6110x->regs[STV6110x_STAT1]);

	for (i = 0; i < TRIALS; i++) {
		stv6110x_read_reg(stv6110x, STV6110x_STAT1, &stv6110x->regs[STV6110x_STAT1]);
		if (!STV6110x_GETFIELD(STAT1_CALRC_STRT, stv6110x->regs[STV6110x_STAT1]))
			break;
		msleep(1);
	}
	STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL3], CTRL3_RCCLK_OFF, 0x1); /* cal. done */
	stv6110x_write_reg(stv6110x, STV6110x_CTRL3, stv6110x->regs[STV6110x_CTRL3]);

	return 0;
}