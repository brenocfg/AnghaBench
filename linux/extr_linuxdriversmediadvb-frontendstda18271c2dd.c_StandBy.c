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
struct tda_state {int* m_Regs; int m_EP3_Standby; } ;

/* Variables and functions */
 size_t EB12 ; 
 size_t EB18 ; 
 size_t EB21 ; 
 size_t EB23 ; 
 size_t EP3 ; 
 int UpdateReg (struct tda_state*,size_t) ; 
 int UpdateRegs (struct tda_state*,size_t,size_t) ; 

__attribute__((used)) static int StandBy(struct tda_state *state)
{
	int status = 0;
	do {
		state->m_Regs[EB12] &= ~0x20;  /* PD_AGC1_Det = 0 */
		status = UpdateReg(state, EB12);
		if (status < 0)
			break;
		state->m_Regs[EB18] &= ~0x83;  /* AGC1_loop_off = 0, AGC1_Gain = 6 dB */
		status = UpdateReg(state, EB18);
		if (status < 0)
			break;
		state->m_Regs[EB21] |= 0x03; /* AGC2_Gain = -6 dB */
		state->m_Regs[EP3] = state->m_EP3_Standby;
		status = UpdateReg(state, EP3);
		if (status < 0)
			break;
		state->m_Regs[EB23] &= ~0x06; /* ForceLP_Fc2_En = 0, LP_Fc[2] = 0 */
		status = UpdateRegs(state, EB21, EB23);
		if (status < 0)
			break;
	} while (0);
	return status;
}