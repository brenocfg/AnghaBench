#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_dsi {int /*<<< orphan*/  clk_parent; TYPE_1__* slave; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 int clk_set_parent (struct clk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dsi_ganged_setup(struct tegra_dsi *dsi)
{
	struct clk *parent;
	int err;

	/* make sure both DSI controllers share the same PLL */
	parent = clk_get_parent(dsi->slave->clk);
	if (!parent)
		return -EINVAL;

	err = clk_set_parent(parent, dsi->clk_parent);
	if (err < 0)
		return err;

	return 0;
}