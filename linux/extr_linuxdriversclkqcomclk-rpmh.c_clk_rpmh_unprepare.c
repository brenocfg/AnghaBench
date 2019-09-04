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
struct clk_rpmh {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_rpmh_aggregate_state_send_command (struct clk_rpmh*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmh_clk_lock ; 
 struct clk_rpmh* to_clk_rpmh (struct clk_hw*) ; 

__attribute__((used)) static void clk_rpmh_unprepare(struct clk_hw *hw)
{
	struct clk_rpmh *c = to_clk_rpmh(hw);

	mutex_lock(&rpmh_clk_lock);
	clk_rpmh_aggregate_state_send_command(c, false);
	mutex_unlock(&rpmh_clk_lock);
}