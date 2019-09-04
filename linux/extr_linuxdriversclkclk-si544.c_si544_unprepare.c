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
struct clk_si544 {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  si544_enable_output (struct clk_si544*,int) ; 
 struct clk_si544* to_clk_si544 (struct clk_hw*) ; 

__attribute__((used)) static void si544_unprepare(struct clk_hw *hw)
{
	struct clk_si544 *data = to_clk_si544(hw);

	si544_enable_output(data, false);
}