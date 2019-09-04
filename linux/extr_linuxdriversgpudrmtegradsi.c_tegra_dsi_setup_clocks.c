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
struct tegra_dsi {int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 int clk_set_parent (struct clk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dsi_setup_clocks(struct tegra_dsi *dsi)
{
	struct clk *parent;
	int err;

	parent = clk_get_parent(dsi->clk);
	if (!parent)
		return -EINVAL;

	err = clk_set_parent(parent, dsi->clk_parent);
	if (err < 0)
		return err;

	return 0;
}