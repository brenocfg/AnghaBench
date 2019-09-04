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
struct sun6i_dsi {struct sun6i_dphy* dphy; } ;
struct sun6i_dphy {int /*<<< orphan*/  reset; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_mmio_detach_clk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 

int sun6i_dphy_remove(struct sun6i_dsi *dsi)
{
	struct sun6i_dphy *dphy = dsi->dphy;

	regmap_mmio_detach_clk(dphy->regs);
	clk_put(dphy->mod_clk);
	clk_put(dphy->bus_clk);
	reset_control_put(dphy->reset);

	return 0;
}