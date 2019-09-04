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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static long clk_pfd_round_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long *prate)
{
	u64 tmp = *prate;
	u8 frac;

	tmp = tmp * 18 + rate / 2;
	do_div(tmp, rate);
	frac = tmp;
	if (frac < 12)
		frac = 12;
	else if (frac > 35)
		frac = 35;
	tmp = *prate;
	tmp *= 18;
	do_div(tmp, frac);

	return tmp;
}