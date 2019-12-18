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
struct tegra_sor {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_out; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,struct clk*) ; 

__attribute__((used)) static int tegra_sor_set_parent_clock(struct tegra_sor *sor, struct clk *parent)
{
	int err;

	clk_disable_unprepare(sor->clk);

	err = clk_set_parent(sor->clk_out, parent);
	if (err < 0)
		return err;

	err = clk_prepare_enable(sor->clk);
	if (err < 0)
		return err;

	return 0;
}