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
 int WriteReg (struct tda_state*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int UpdateReg(struct tda_state *state, u8 Reg)
{
	return WriteReg(state, Reg, state->m_Regs[Reg]);
}