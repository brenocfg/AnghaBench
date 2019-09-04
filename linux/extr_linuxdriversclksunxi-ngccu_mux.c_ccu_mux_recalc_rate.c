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
struct ccu_mux {int /*<<< orphan*/  mux; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 unsigned long ccu_mux_helper_apply_prediv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned long) ; 
 struct ccu_mux* hw_to_ccu_mux (struct clk_hw*) ; 

__attribute__((used)) static unsigned long ccu_mux_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct ccu_mux *cm = hw_to_ccu_mux(hw);

	return ccu_mux_helper_apply_prediv(&cm->common, &cm->mux, -1,
					   parent_rate);
}