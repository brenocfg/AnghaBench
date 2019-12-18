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
typedef  unsigned int u8 ;
struct si2165_state {unsigned int sys_clk; unsigned int fvco_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PLL_DIVL ; 
 int si2165_writereg8 (struct si2165_state*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int si2165_adjust_pll_divl(struct si2165_state *state, u8 divl)
{
	state->sys_clk = state->fvco_hz / (divl * 2u);
	return si2165_writereg8(state, REG_PLL_DIVL, divl);
}