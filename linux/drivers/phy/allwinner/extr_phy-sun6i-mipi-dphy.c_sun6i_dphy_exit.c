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
struct sun6i_dphy {int /*<<< orphan*/  reset; int /*<<< orphan*/  mod_clk; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_rate_exclusive_put (int /*<<< orphan*/ ) ; 
 struct sun6i_dphy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dphy_exit(struct phy *phy)
{
	struct sun6i_dphy *dphy = phy_get_drvdata(phy);

	clk_rate_exclusive_put(dphy->mod_clk);
	clk_disable_unprepare(dphy->mod_clk);
	reset_control_assert(dphy->reset);

	return 0;
}