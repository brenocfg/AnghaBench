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
typedef  unsigned long u64 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 unsigned long MHZ ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 

__attribute__((used)) static long pll_clk_round_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long *parent_rate)
{
	unsigned long fin, nf, nr, od;
	u64 dividend;

	/*
	 * fout = fin * nf / (nr * od);
	 * set od = 1, nr = fin/MHz, so fout = nf * MHz
	 */
	rate = rate - rate % MHZ;

	nf = rate / MHZ;
	if (nf > BIT(13))
		nf = BIT(13);
	if (nf < 1)
		nf = 1;

	fin = *parent_rate;

	nr = fin / MHZ;
	if (nr > BIT(6))
		nr = BIT(6);
	od = 1;

	dividend = (u64)fin * nf;
	do_div(dividend, nr * od);

	return (long)dividend;
}