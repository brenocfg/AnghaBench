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
 int alchemy_rdsys (int /*<<< orphan*/ ) ; 
 struct alchemy_fgcs_clk* to_fgcs_clk (struct clk_hw*) ; 

__attribute__((used)) static int alchemy_clk_fgv1_isen(struct clk_hw *hw)
{
	struct alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	unsigned long v = alchemy_rdsys(c->reg) >> (c->shift + 1);

	return v & 1;
}