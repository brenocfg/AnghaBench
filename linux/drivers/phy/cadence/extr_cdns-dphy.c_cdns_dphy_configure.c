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
union phy_configure_opts {int /*<<< orphan*/  mipi_dphy; } ;
struct phy {int dummy; } ;
struct cdns_dphy_cfg {int /*<<< orphan*/  member_0; } ;
struct cdns_dphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_CLK_CFG_LEFT_DRIVES_LEFT ; 
 int cdns_dphy_config_from_opts (struct phy*,int /*<<< orphan*/ *,struct cdns_dphy_cfg*) ; 
 int /*<<< orphan*/  cdns_dphy_set_clk_lane_cfg (struct cdns_dphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_dphy_set_pll_cfg (struct cdns_dphy*,struct cdns_dphy_cfg*) ; 
 int cdns_dphy_setup_psm (struct cdns_dphy*) ; 
 struct cdns_dphy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int cdns_dphy_configure(struct phy *phy, union phy_configure_opts *opts)
{
	struct cdns_dphy *dphy = phy_get_drvdata(phy);
	struct cdns_dphy_cfg cfg = { 0 };
	int ret;

	ret = cdns_dphy_config_from_opts(phy, &opts->mipi_dphy, &cfg);
	if (ret)
		return ret;

	/*
	 * Configure the internal PSM clk divider so that the DPHY has a
	 * 1MHz clk (or something close).
	 */
	ret = cdns_dphy_setup_psm(dphy);
	if (ret)
		return ret;

	/*
	 * Configure attach clk lanes to data lanes: the DPHY has 2 clk lanes
	 * and 8 data lanes, each clk lane can be attache different set of
	 * data lanes. The 2 groups are named 'left' and 'right', so here we
	 * just say that we want the 'left' clk lane to drive the 'left' data
	 * lanes.
	 */
	cdns_dphy_set_clk_lane_cfg(dphy, DPHY_CLK_CFG_LEFT_DRIVES_LEFT);

	/*
	 * Configure the DPHY PLL that will be used to generate the TX byte
	 * clk.
	 */
	cdns_dphy_set_pll_cfg(dphy, &cfg);

	return 0;
}