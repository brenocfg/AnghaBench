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
typedef  int u16 ;
struct clk_syscon {int /*<<< orphan*/  en_bit; int /*<<< orphan*/  en_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int readw (int /*<<< orphan*/ ) ; 
 struct clk_syscon* to_syscon (struct clk_hw*) ; 

__attribute__((used)) static int syscon_clk_is_enabled(struct clk_hw *hw)
{
	struct clk_syscon *sclk = to_syscon(hw);
	u16 val;

	/* If no enable register defined, it's always-on */
	if (!sclk->en_reg)
		return 1;

	val = readw(sclk->en_reg);
	val &= BIT(sclk->en_bit);

	return val ? 1 : 0;
}