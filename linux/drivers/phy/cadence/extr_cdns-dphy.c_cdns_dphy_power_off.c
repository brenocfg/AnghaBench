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
struct phy {int dummy; } ;
struct cdns_dphy {int /*<<< orphan*/  psm_clk; int /*<<< orphan*/  pll_ref_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct cdns_dphy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int cdns_dphy_power_off(struct phy *phy)
{
	struct cdns_dphy *dphy = phy_get_drvdata(phy);

	clk_disable_unprepare(dphy->pll_ref_clk);
	clk_disable_unprepare(dphy->psm_clk);

	return 0;
}