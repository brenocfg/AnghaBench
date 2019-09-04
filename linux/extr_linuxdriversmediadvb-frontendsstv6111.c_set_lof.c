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
typedef  int u32 ;
struct stv {int ref_freq; int* reg; int frequency; } ;

/* Variables and functions */
 int muldiv32 (int,int,int) ; 
 int /*<<< orphan*/  read_reg (struct stv*,int,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_for_call_done (struct stv*,int) ; 
 int /*<<< orphan*/  write_regs (struct stv*,int,int) ; 

__attribute__((used)) static int set_lof(struct stv *state, u32 local_frequency, u32 cutoff_frequency)
{
	u32 index = (cutoff_frequency + 999999) / 1000000;
	u32 frequency = (local_frequency + 500) / 1000;
	u32 p = 1, psel = 0, fvco, div, frac;
	u8 icp, tmp;

	if (index < 6)
		index = 6;
	if (index > 50)
		index = 50;

	if (frequency <= 1300000) {
		p =  4;
		psel = 1;
	} else {
		p =  2;
		psel = 0;
	}
	fvco = frequency * p;
	div = fvco / state->ref_freq;
	frac = fvco % state->ref_freq;
	frac = muldiv32(frac, 0x40000, state->ref_freq);

	icp = 0;
	if (fvco < 2700000)
		icp = 0;
	else if (fvco < 2950000)
		icp = 1;
	else if (fvco < 3300000)
		icp = 2;
	else if (fvco < 3700000)
		icp = 3;
	else if (fvco < 4200000)
		icp = 5;
	else if (fvco < 4800000)
		icp = 6;
	else
		icp = 7;

	state->reg[0x02] |= 0x80; /* LNA IIP3 Mode */

	state->reg[0x03] = (state->reg[0x03] & ~0x80) | (psel << 7);
	state->reg[0x04] = (div & 0xFF);
	state->reg[0x05] = (((div >> 8) & 0x01) | ((frac & 0x7F) << 1)) & 0xff;
	state->reg[0x06] = ((frac >> 7) & 0xFF);
	state->reg[0x07] = (state->reg[0x07] & ~0x07) | ((frac >> 15) & 0x07);
	state->reg[0x07] = (state->reg[0x07] & ~0xE0) | (icp << 5);

	state->reg[0x08] = (state->reg[0x08] & ~0xFC) | ((index - 6) << 2);
	/* Start cal vco,CF */
	state->reg[0x09] = (state->reg[0x09] & ~0x0C) | 0x0C;
	write_regs(state, 2, 8);

	wait_for_call_done(state, 0x0C);

	usleep_range(10000, 12000);

	read_reg(state, 0x03, &tmp);
	if (tmp & 0x10)	{
		state->reg[0x02] &= ~0x80; /* LNA NF Mode */
		write_regs(state, 2, 1);
	}
	read_reg(state, 0x08, &tmp);

	state->frequency = frequency;

	return 0;
}