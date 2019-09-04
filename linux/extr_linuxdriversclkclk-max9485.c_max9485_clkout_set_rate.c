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
struct max9485_rate {unsigned long out; int /*<<< orphan*/  reg_value; } ;
struct max9485_clk_hw {int /*<<< orphan*/  drvdata; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX9485_FREQ_MASK ; 
 struct max9485_rate* max9485_rates ; 
 int max9485_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max9485_clk_hw* to_max9485_clk (struct clk_hw*) ; 

__attribute__((used)) static int max9485_clkout_set_rate(struct clk_hw *hw, unsigned long rate,
				   unsigned long parent_rate)
{
	struct max9485_clk_hw *clk_hw = to_max9485_clk(hw);
	const struct max9485_rate *entry;

	for (entry = max9485_rates; entry->out != 0; entry++)
		if (entry->out == rate)
			break;

	if (entry->out == 0)
		return -EINVAL;

	return max9485_update_bits(clk_hw->drvdata,
				   MAX9485_FREQ_MASK,
				   entry->reg_value);
}