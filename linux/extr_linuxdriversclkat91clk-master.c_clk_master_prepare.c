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
struct clk_master {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_master_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct clk_master* to_clk_master (struct clk_hw*) ; 

__attribute__((used)) static int clk_master_prepare(struct clk_hw *hw)
{
	struct clk_master *master = to_clk_master(hw);

	while (!clk_master_ready(master->regmap))
		cpu_relax();

	return 0;
}