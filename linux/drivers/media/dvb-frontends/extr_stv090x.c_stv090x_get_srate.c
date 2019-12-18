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
struct stv090x_state {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  SFR0 ; 
 int /*<<< orphan*/  SFR1 ; 
 int /*<<< orphan*/  SFR2 ; 
 int /*<<< orphan*/  SFR3 ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stv090x_get_srate(struct stv090x_state *state, u32 clk)
{
	u8 r3, r2, r1, r0;
	s32 srate, int_1, int_2, tmp_1, tmp_2;

	r3 = STV090x_READ_DEMOD(state, SFR3);
	r2 = STV090x_READ_DEMOD(state, SFR2);
	r1 = STV090x_READ_DEMOD(state, SFR1);
	r0 = STV090x_READ_DEMOD(state, SFR0);

	srate = ((r3 << 24) | (r2 << 16) | (r1 <<  8) | r0);

	int_1 = clk >> 16;
	int_2 = srate >> 16;

	tmp_1 = clk % 0x10000;
	tmp_2 = srate % 0x10000;

	srate = (int_1 * int_2) +
		((int_1 * tmp_2) >> 16) +
		((int_2 * tmp_1) >> 16);

	return srate;
}