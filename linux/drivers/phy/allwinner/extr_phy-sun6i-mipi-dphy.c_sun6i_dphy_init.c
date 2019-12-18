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
struct sun6i_dphy {int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate_exclusive (int /*<<< orphan*/ ,int) ; 
 struct sun6i_dphy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dphy_init(struct phy *phy)
{
	struct sun6i_dphy *dphy = phy_get_drvdata(phy);

	reset_control_deassert(dphy->reset);
	clk_prepare_enable(dphy->mod_clk);
	clk_set_rate_exclusive(dphy->mod_clk, 150000000);

	return 0;
}