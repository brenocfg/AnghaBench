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
struct sprd_gate {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_gate_toggle (struct sprd_gate*,int) ; 
 struct sprd_gate* hw_to_sprd_gate (struct clk_hw*) ; 

__attribute__((used)) static void sprd_gate_disable(struct clk_hw *hw)
{
	struct sprd_gate *sg = hw_to_sprd_gate(hw);

	clk_gate_toggle(sg, false);
}