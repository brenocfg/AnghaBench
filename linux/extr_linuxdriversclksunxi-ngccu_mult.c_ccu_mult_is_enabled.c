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
struct ccu_mult {int /*<<< orphan*/  enable; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int ccu_gate_helper_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ccu_mult* hw_to_ccu_mult (struct clk_hw*) ; 

__attribute__((used)) static int ccu_mult_is_enabled(struct clk_hw *hw)
{
	struct ccu_mult *cm = hw_to_ccu_mult(hw);

	return ccu_gate_helper_is_enabled(&cm->common, cm->enable);
}