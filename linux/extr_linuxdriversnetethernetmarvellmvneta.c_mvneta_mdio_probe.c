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
struct mvneta_port {TYPE_1__* dev; int /*<<< orphan*/  phylink; int /*<<< orphan*/  dn; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  supported; int /*<<< orphan*/  cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_GWOL ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  phylink_ethtool_get_wol (int /*<<< orphan*/ ,struct ethtool_wolinfo*) ; 
 int phylink_of_phy_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvneta_mdio_probe(struct mvneta_port *pp)
{
	struct ethtool_wolinfo wol = { .cmd = ETHTOOL_GWOL };
	int err = phylink_of_phy_connect(pp->phylink, pp->dn, 0);

	if (err)
		netdev_err(pp->dev, "could not attach PHY: %d\n", err);

	phylink_ethtool_get_wol(pp->phylink, &wol);
	device_set_wakeup_capable(&pp->dev->dev, !!wol.supported);

	return err;
}