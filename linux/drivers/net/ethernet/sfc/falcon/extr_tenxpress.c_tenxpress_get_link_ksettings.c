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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct ef4_nic {int /*<<< orphan*/  mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseT_Full ; 
 scalar_t__ LOOPBACK_EXTERNAL (struct ef4_nic*) ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_CTRL ; 
 int MDIO_AN_10GBT_CTRL_ADV10G ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_STAT ; 
 int MDIO_AN_10GBT_STAT_LP10G ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int ef4_mdio_read (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio45_ethtool_ksettings_get_npage (int /*<<< orphan*/ *,struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tenxpress_get_link_ksettings(struct ef4_nic *efx,
			     struct ethtool_link_ksettings *cmd)
{
	u32 adv = 0, lpa = 0;
	int reg;

	reg = ef4_mdio_read(efx, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL);
	if (reg & MDIO_AN_10GBT_CTRL_ADV10G)
		adv |= ADVERTISED_10000baseT_Full;
	reg = ef4_mdio_read(efx, MDIO_MMD_AN, MDIO_AN_10GBT_STAT);
	if (reg & MDIO_AN_10GBT_STAT_LP10G)
		lpa |= ADVERTISED_10000baseT_Full;

	mdio45_ethtool_ksettings_get_npage(&efx->mdio, cmd, adv, lpa);

	/* In loopback, the PHY automatically brings up the correct interface,
	 * but doesn't advertise the correct speed. So override it */
	if (LOOPBACK_EXTERNAL(efx))
		cmd->base.speed = SPEED_10000;
}