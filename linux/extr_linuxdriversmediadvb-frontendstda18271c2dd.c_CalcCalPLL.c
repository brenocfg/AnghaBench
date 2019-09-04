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
typedef  int u64 ;
typedef  int u32 ;
struct tda_state {int* m_Regs; } ;

/* Variables and functions */
 size_t CD1 ; 
 size_t CD2 ; 
 size_t CD3 ; 
 size_t CPD ; 
 int EINVAL ; 
 int /*<<< orphan*/  SearchMap3 (int /*<<< orphan*/ ,int,int*,int*) ; 
 int UpdateRegs (struct tda_state*,size_t,size_t) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  m_Cal_PLL_Map ; 

__attribute__((used)) static int CalcCalPLL(struct tda_state *state, u32 freq)
{
	u8 PostDiv;
	u8 Div;
	u64 OscFreq;
	u32 CalDiv;

	if (!SearchMap3(m_Cal_PLL_Map, freq, &PostDiv, &Div))
		return -EINVAL;

	OscFreq = (u64)freq * (u64)Div;
	/* CalDiv = u32( OscFreq * 16384 / 16000000 ); */
	OscFreq *= (u64)16384;
	do_div(OscFreq, (u64)16000000);
	CalDiv = OscFreq;

	state->m_Regs[CPD] = PostDiv;
	state->m_Regs[CD1] = ((CalDiv >> 16) & 0xFF);
	state->m_Regs[CD2] = ((CalDiv >>  8) & 0xFF);
	state->m_Regs[CD3] = (CalDiv & 0xFF);

	return UpdateRegs(state, CPD, CD3);
}