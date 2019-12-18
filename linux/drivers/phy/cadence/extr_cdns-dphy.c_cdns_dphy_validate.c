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
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
 int PHY_MODE_MIPI_DPHY ; 
 int cdns_dphy_config_from_opts (struct phy*,int /*<<< orphan*/ *,struct cdns_dphy_cfg*) ; 

__attribute__((used)) static int cdns_dphy_validate(struct phy *phy, enum phy_mode mode, int submode,
			      union phy_configure_opts *opts)
{
	struct cdns_dphy_cfg cfg = { 0 };

	if (mode != PHY_MODE_MIPI_DPHY)
		return -EINVAL;

	return cdns_dphy_config_from_opts(phy, &opts->mipi_dphy, &cfg);
}