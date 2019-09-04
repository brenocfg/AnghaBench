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
struct clk_pfd {int idx; scalar_t__ reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLR ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 
 struct clk_pfd* to_clk_pfd (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int clk_pfd_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_pfd *pfd = to_clk_pfd(hw);
	u64 tmp = parent_rate;
	u8 frac;

	tmp = tmp * 18 + rate / 2;
	do_div(tmp, rate);
	frac = tmp;
	if (frac < 12)
		frac = 12;
	else if (frac > 35)
		frac = 35;

	writel_relaxed(0x3f << (pfd->idx * 8), pfd->reg + CLR);
	writel_relaxed(frac << (pfd->idx * 8), pfd->reg + SET);

	return 0;
}