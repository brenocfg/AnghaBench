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
struct clk_pfd {int idx; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pfd* to_clk_pfd (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pfd_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct clk_pfd *pfd = to_clk_pfd(hw);
	u64 tmp = parent_rate;
	u8 frac = (readl_relaxed(pfd->reg) >> (pfd->idx * 8)) & 0x3f;

	tmp *= 18;
	do_div(tmp, frac);

	return tmp;
}