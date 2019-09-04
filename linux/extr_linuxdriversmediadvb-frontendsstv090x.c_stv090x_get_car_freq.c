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
typedef  int u32 ;
struct stv090x_state {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CFR0 ; 
 int /*<<< orphan*/  CFR1 ; 
 int /*<<< orphan*/  CFR2 ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int comp2 (int,int) ; 

__attribute__((used)) static s32 stv090x_get_car_freq(struct stv090x_state *state, u32 mclk)
{
	s32 derot, int_1, int_2, tmp_1, tmp_2;

	derot  = STV090x_READ_DEMOD(state, CFR2) << 16;
	derot |= STV090x_READ_DEMOD(state, CFR1) <<  8;
	derot |= STV090x_READ_DEMOD(state, CFR0);

	derot = comp2(derot, 24);
	int_1 = mclk >> 12;
	int_2 = derot >> 12;

	/* carrier_frequency = MasterClock * Reg / 2^24 */
	tmp_1 = mclk % 0x1000;
	tmp_2 = derot % 0x1000;

	derot = (int_1 * int_2) +
		((int_1 * tmp_2) >> 12) +
		((int_2 * tmp_1) >> 12);

	return derot;
}