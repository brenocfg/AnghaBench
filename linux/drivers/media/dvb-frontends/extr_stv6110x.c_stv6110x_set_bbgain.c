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
typedef  int u32 ;
struct stv6110x_state {int /*<<< orphan*/ * regs; } ;
struct dvb_frontend {struct stv6110x_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL2_BBGAIN ; 
 size_t STV6110x_CTRL2 ; 
 int /*<<< orphan*/  STV6110x_SETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv6110x_write_reg (struct stv6110x_state*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv6110x_set_bbgain(struct dvb_frontend *fe, u32 gain)
{
	struct stv6110x_state *stv6110x = fe->tuner_priv;

	STV6110x_SETFIELD(stv6110x->regs[STV6110x_CTRL2], CTRL2_BBGAIN, gain / 2);
	stv6110x_write_reg(stv6110x, STV6110x_CTRL2, stv6110x->regs[STV6110x_CTRL2]);

	return 0;
}