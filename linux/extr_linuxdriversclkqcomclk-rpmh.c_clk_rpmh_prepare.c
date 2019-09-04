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
 int clk_rpmh_aggregate_state_send_command (struct clk_rpmh*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmh_clk_lock ; 
 struct clk_rpmh* to_clk_rpmh (struct clk_hw*) ; 

__attribute__((used)) static int clk_rpmh_prepare(struct clk_hw *hw)
{
	struct clk_rpmh *c = to_clk_rpmh(hw);
	int ret = 0;

	mutex_lock(&rpmh_clk_lock);
	ret = clk_rpmh_aggregate_state_send_command(c, true);
	mutex_unlock(&rpmh_clk_lock);

	return ret;
}