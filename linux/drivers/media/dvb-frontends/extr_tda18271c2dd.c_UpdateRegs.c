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
typedef  size_t u8 ;
struct tda_state {int /*<<< orphan*/ * m_Regs; } ;

/* Variables and functions */
 int WriteRegs (struct tda_state*,size_t,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int UpdateRegs(struct tda_state *state, u8 RegFrom, u8 RegTo)
{
	return WriteRegs(state, RegFrom,
			 &state->m_Regs[RegFrom], RegTo-RegFrom+1);
}