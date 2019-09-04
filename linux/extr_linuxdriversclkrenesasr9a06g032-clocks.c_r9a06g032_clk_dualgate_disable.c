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
struct r9a06g032_clk_dualgate {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r9a06g032_clk_dualgate_setenable (struct r9a06g032_clk_dualgate*,int /*<<< orphan*/ ) ; 
 struct r9a06g032_clk_dualgate* to_clk_dualgate (struct clk_hw*) ; 

__attribute__((used)) static void r9a06g032_clk_dualgate_disable(struct clk_hw *hw)
{
	struct r9a06g032_clk_dualgate *gate = to_clk_dualgate(hw);

	r9a06g032_clk_dualgate_setenable(gate, 0);
}