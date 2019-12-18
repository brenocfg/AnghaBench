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
struct tda_state {int* m_Regs; } ;

/* Variables and functions */
 size_t CD1 ; 
 size_t CD2 ; 
 size_t CD3 ; 
 size_t CPD ; 
 size_t EB17 ; 
 size_t EB23 ; 
 size_t EB4 ; 
 size_t EP1 ; 
 size_t EP2 ; 
 size_t EP3 ; 
 size_t EP4 ; 
 size_t EP5 ; 
 size_t MD1 ; 
 size_t MD2 ; 
 size_t MD3 ; 
 size_t MPD ; 
 size_t TM ; 
 int UpdateReg (struct tda_state*,size_t) ; 
 int UpdateRegs (struct tda_state*,size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int FixedContentsI2CUpdate(struct tda_state *state)
{
	static u8 InitRegs[] = {
		0x08, 0x80, 0xC6,
		0xDF, 0x16, 0x60, 0x80,
		0x80, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0xFC, 0x01, 0x84, 0x41,
		0x01, 0x84, 0x40, 0x07,
		0x00, 0x00, 0x96, 0x3F,
		0xC1, 0x00, 0x8F, 0x00,
		0x00, 0x8C, 0x00, 0x20,
		0xB3, 0x48, 0xB0,
	};
	int status = 0;
	memcpy(&state->m_Regs[TM], InitRegs, EB23 - TM + 1);
	do {
		status = UpdateRegs(state, TM, EB23);
		if (status < 0)
			break;

		/* AGC1 gain setup */
		state->m_Regs[EB17] = 0x00;
		status = UpdateReg(state, EB17);
		if (status < 0)
			break;
		state->m_Regs[EB17] = 0x03;
		status = UpdateReg(state, EB17);
		if (status < 0)
			break;
		state->m_Regs[EB17] = 0x43;
		status = UpdateReg(state, EB17);
		if (status < 0)
			break;
		state->m_Regs[EB17] = 0x4C;
		status = UpdateReg(state, EB17);
		if (status < 0)
			break;

		/* IRC Cal Low band */
		state->m_Regs[EP3] = 0x1F;
		state->m_Regs[EP4] = 0x66;
		state->m_Regs[EP5] = 0x81;
		state->m_Regs[CPD] = 0xCC;
		state->m_Regs[CD1] = 0x6C;
		state->m_Regs[CD2] = 0x00;
		state->m_Regs[CD3] = 0x00;
		state->m_Regs[MPD] = 0xC5;
		state->m_Regs[MD1] = 0x77;
		state->m_Regs[MD2] = 0x08;
		state->m_Regs[MD3] = 0x00;
		status = UpdateRegs(state, EP2, MD3); /* diff between sw and datasheet (ep3-md3) */
		if (status < 0)
			break;

#if 0
		state->m_Regs[EB4] = 0x61;          /* missing in sw */
		status = UpdateReg(state, EB4);
		if (status < 0)
			break;
		msleep(1);
		state->m_Regs[EB4] = 0x41;
		status = UpdateReg(state, EB4);
		if (status < 0)
			break;
#endif

		msleep(5);
		status = UpdateReg(state, EP1);
		if (status < 0)
			break;
		msleep(5);

		state->m_Regs[EP5] = 0x85;
		state->m_Regs[CPD] = 0xCB;
		state->m_Regs[CD1] = 0x66;
		state->m_Regs[CD2] = 0x70;
		status = UpdateRegs(state, EP3, CD3);
		if (status < 0)
			break;
		msleep(5);
		status = UpdateReg(state, EP2);
		if (status < 0)
			break;
		msleep(30);

		/* IRC Cal mid band */
		state->m_Regs[EP5] = 0x82;
		state->m_Regs[CPD] = 0xA8;
		state->m_Regs[CD2] = 0x00;
		state->m_Regs[MPD] = 0xA1; /* Datasheet = 0xA9 */
		state->m_Regs[MD1] = 0x73;
		state->m_Regs[MD2] = 0x1A;
		status = UpdateRegs(state, EP3, MD3);
		if (status < 0)
			break;

		msleep(5);
		status = UpdateReg(state, EP1);
		if (status < 0)
			break;
		msleep(5);

		state->m_Regs[EP5] = 0x86;
		state->m_Regs[CPD] = 0xA8;
		state->m_Regs[CD1] = 0x66;
		state->m_Regs[CD2] = 0xA0;
		status = UpdateRegs(state, EP3, CD3);
		if (status < 0)
			break;
		msleep(5);
		status = UpdateReg(state, EP2);
		if (status < 0)
			break;
		msleep(30);

		/* IRC Cal high band */
		state->m_Regs[EP5] = 0x83;
		state->m_Regs[CPD] = 0x98;
		state->m_Regs[CD1] = 0x65;
		state->m_Regs[CD2] = 0x00;
		state->m_Regs[MPD] = 0x91;  /* Datasheet = 0x91 */
		state->m_Regs[MD1] = 0x71;
		state->m_Regs[MD2] = 0xCD;
		status = UpdateRegs(state, EP3, MD3);
		if (status < 0)
			break;
		msleep(5);
		status = UpdateReg(state, EP1);
		if (status < 0)
			break;
		msleep(5);
		state->m_Regs[EP5] = 0x87;
		state->m_Regs[CD1] = 0x65;
		state->m_Regs[CD2] = 0x50;
		status = UpdateRegs(state, EP3, CD3);
		if (status < 0)
			break;
		msleep(5);
		status = UpdateReg(state, EP2);
		if (status < 0)
			break;
		msleep(30);

		/* Back to normal */
		state->m_Regs[EP4] = 0x64;
		status = UpdateReg(state, EP4);
		if (status < 0)
			break;
		status = UpdateReg(state, EP1);
		if (status < 0)
			break;

	} while (0);
	return status;
}