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
typedef  int u16 ;
struct stv {TYPE_1__* base; scalar_t__ nr; } ;
struct TYPE_2__ {int mclk; } ;

/* Variables and functions */
 int RSTV0910_P1_DISRXCFG ; 
 int RSTV0910_P1_DISTXCFG ; 
 int RSTV0910_P1_DISTXF22 ; 
 int /*<<< orphan*/  write_reg (struct stv*,int,int) ; 

__attribute__((used)) static int init_diseqc(struct stv *state)
{
	u16 offs = state->nr ? 0x40 : 0; /* Address offset */
	u8 freq = ((state->base->mclk + 11000 * 32) / (22000 * 32));

	/* Disable receiver */
	write_reg(state, RSTV0910_P1_DISRXCFG + offs, 0x00);
	write_reg(state, RSTV0910_P1_DISTXCFG + offs, 0xBA); /* Reset = 1 */
	write_reg(state, RSTV0910_P1_DISTXCFG + offs, 0x3A); /* Reset = 0 */
	write_reg(state, RSTV0910_P1_DISTXF22 + offs, freq);
	return 0;
}