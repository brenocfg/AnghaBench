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
struct max9485_clk_hw {int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  drvdata; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max9485_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max9485_clk_hw* to_max9485_clk (struct clk_hw*) ; 

__attribute__((used)) static void max9485_clk_unprepare(struct clk_hw *hw)
{
	struct max9485_clk_hw *clk_hw = to_max9485_clk(hw);

	max9485_update_bits(clk_hw->drvdata, clk_hw->enable_bit, 0);
}