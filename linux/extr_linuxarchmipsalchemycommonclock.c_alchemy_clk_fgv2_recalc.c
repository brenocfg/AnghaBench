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
struct clk_hw {int dummy; } ;
struct alchemy_fgcs_clk {int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned long alchemy_rdsys (int /*<<< orphan*/ ) ; 
 struct alchemy_fgcs_clk* to_fgcs_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long alchemy_clk_fgv2_recalc(struct clk_hw *hw,
					     unsigned long parent_rate)
{
	struct alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	int sh = c->shift + 2;
	unsigned long v, t;

	v = alchemy_rdsys(c->reg);
	t = parent_rate / (((v >> sh) & 0xff) + 1);
	if ((v & (1 << 30)) == 0)		/* test scale bit */
		t /= 2;

	return t;
}