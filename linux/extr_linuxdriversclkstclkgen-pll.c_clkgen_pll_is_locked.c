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
typedef  int /*<<< orphan*/  u32 ;
struct clkgen_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKGEN_READ (struct clkgen_pll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locked_status ; 
 struct clkgen_pll* to_clkgen_pll (struct clk_hw*) ; 

__attribute__((used)) static int clkgen_pll_is_locked(struct clk_hw *hw)
{
	struct clkgen_pll *pll = to_clkgen_pll(hw);
	u32 locked = CLKGEN_READ(pll, locked_status);

	return !!locked;
}