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
struct ccu_nkmp {int /*<<< orphan*/  enable; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int ccu_gate_helper_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ccu_nkmp* hw_to_ccu_nkmp (struct clk_hw*) ; 

__attribute__((used)) static int ccu_nkmp_enable(struct clk_hw *hw)
{
	struct ccu_nkmp *nkmp = hw_to_ccu_nkmp(hw);

	return ccu_gate_helper_enable(&nkmp->common, nkmp->enable);
}