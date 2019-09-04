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
struct owl_clk_common {int dummy; } ;
struct owl_gate {int /*<<< orphan*/  gate_hw; struct owl_clk_common common; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct owl_gate* hw_to_owl_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  owl_gate_set (struct owl_clk_common*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int owl_gate_enable(struct clk_hw *hw)
{
	struct owl_gate *gate = hw_to_owl_gate(hw);
	struct owl_clk_common *common = &gate->common;

	owl_gate_set(common, &gate->gate_hw, true);

	return 0;
}