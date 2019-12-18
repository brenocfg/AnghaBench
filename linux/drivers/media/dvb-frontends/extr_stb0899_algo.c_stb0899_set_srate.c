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
struct stb0899_state {int /*<<< orphan*/  verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STB0899_SFRH ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int stb0899_do_div (int,int) ; 
 int /*<<< orphan*/  stb0899_write_regs (struct stb0899_state*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static u32 stb0899_set_srate(struct stb0899_state *state, u32 master_clk, u32 srate)
{
	u32 tmp;
	u8 sfr[3];

	dprintk(state->verbose, FE_DEBUG, 1, "-->");
	/*
	 * in order to have the maximum precision, the symbol rate entered into
	 * the chip is computed as the closest value of the "true value".
	 * In this purpose, the symbol rate value is rounded (1 is added on the bit
	 * below the LSB )
	 *
	 * srate = (SFR * master_clk) >> 20
	 *      <=>
	 *   SFR = srate << 20 / master_clk
	 *
	 * rounded:
	 *   SFR = (srate << 21 + master_clk) / (2 * master_clk)
	 *
	 * stored as 20 bit number with an offset of 4 bit:
	 *   sfr = SFR << 4;
	 */

	tmp = stb0899_do_div((((u64)srate) << 21) + master_clk, 2 * master_clk);
	tmp <<= 4;

	sfr[0] = tmp >> 16;
	sfr[1] = tmp >>  8;
	sfr[2] = tmp;

	stb0899_write_regs(state, STB0899_SFRH, sfr, 3);

	return srate;
}