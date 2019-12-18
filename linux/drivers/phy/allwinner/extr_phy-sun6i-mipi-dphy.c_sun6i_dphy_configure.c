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
struct sun6i_dphy {int /*<<< orphan*/  config; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union phy_configure_opts*,int) ; 
 struct sun6i_dphy* phy_get_drvdata (struct phy*) ; 
 int phy_mipi_dphy_config_validate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun6i_dphy_configure(struct phy *phy, union phy_configure_opts *opts)
{
	struct sun6i_dphy *dphy = phy_get_drvdata(phy);
	int ret;

	ret = phy_mipi_dphy_config_validate(&opts->mipi_dphy);
	if (ret)
		return ret;

	memcpy(&dphy->config, opts, sizeof(dphy->config));

	return 0;
}