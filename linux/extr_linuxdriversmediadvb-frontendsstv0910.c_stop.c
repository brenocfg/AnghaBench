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
typedef  int u8 ;
struct stv {int tscfgh; int /*<<< orphan*/  receive_mode; scalar_t__ started; scalar_t__ regoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCVMODE_NONE ; 
 scalar_t__ RSTV0910_P2_AGC2O ; 
 scalar_t__ RSTV0910_P2_DMDISTATE ; 
 scalar_t__ RSTV0910_P2_PDELCTRL1 ; 
 scalar_t__ RSTV0910_P2_TSCFGH ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,int*) ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 

__attribute__((used)) static int stop(struct stv *state)
{
	if (state->started) {
		u8 tmp;

		write_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh | 0x01);
		read_reg(state, RSTV0910_P2_PDELCTRL1 + state->regoff, &tmp);
		tmp &= ~0x01; /* release reset DVBS2 packet delin */
		write_reg(state, RSTV0910_P2_PDELCTRL1 + state->regoff, tmp);
		/* Blind optim*/
		write_reg(state, RSTV0910_P2_AGC2O + state->regoff, 0x5B);
		/* Stop the demod */
		write_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x5c);
		state->started = 0;
	}
	state->receive_mode = RCVMODE_NONE;
	return 0;
}