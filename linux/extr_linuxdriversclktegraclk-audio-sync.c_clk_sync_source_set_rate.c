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
struct tegra_clk_sync_source {unsigned long rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct tegra_clk_sync_source* to_clk_sync_source (struct clk_hw*) ; 

__attribute__((used)) static int clk_sync_source_set_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long parent_rate)
{
	struct tegra_clk_sync_source *sync = to_clk_sync_source(hw);

	sync->rate = rate;
	return 0;
}