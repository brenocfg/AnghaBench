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
struct cdns_dphy {TYPE_1__* ops; } ;
typedef  enum cdns_dphy_clk_lane_cfg { ____Placeholder_cdns_dphy_clk_lane_cfg } cdns_dphy_clk_lane_cfg ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_clk_lane_cfg ) (struct cdns_dphy*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cdns_dphy*,int) ; 

__attribute__((used)) static void cdns_dphy_set_clk_lane_cfg(struct cdns_dphy *dphy,
				       enum cdns_dphy_clk_lane_cfg cfg)
{
	if (dphy->ops->set_clk_lane_cfg)
		dphy->ops->set_clk_lane_cfg(dphy, cfg);
}