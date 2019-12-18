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
struct cdns_dp_phy {unsigned int num_lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns_dp_phy_pma_cmn_cfg_25mhz (struct cdns_dp_phy*) ; 
 int /*<<< orphan*/  cdns_dp_phy_pma_lane_cfg (struct cdns_dp_phy*,unsigned int) ; 

__attribute__((used)) static void cdns_dp_phy_pma_cfg(struct cdns_dp_phy *cdns_phy)
{
	unsigned int i;

	/* PMA common configuration */
	cdns_dp_phy_pma_cmn_cfg_25mhz(cdns_phy);

	/* PMA lane configuration to deal with multi-link operation */
	for (i = 0; i < cdns_phy->num_lanes; i++)
		cdns_dp_phy_pma_lane_cfg(cdns_phy, i);
}