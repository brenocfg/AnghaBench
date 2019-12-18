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
typedef  int /*<<< orphan*/  u32 ;
struct phylink_config {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct mvneta_port {int eee_active; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_GMAC_AUTONEG_CONFIG ; 
 int /*<<< orphan*/  MVNETA_GMAC_FORCE_LINK_DOWN ; 
 int /*<<< orphan*/  MVNETA_GMAC_FORCE_LINK_PASS ; 
 int /*<<< orphan*/  mvneta_port_down (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_set_eee (struct mvneta_port*,int) ; 
 int /*<<< orphan*/  mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phylink_autoneg_inband (unsigned int) ; 
 struct net_device* to_net_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_mac_link_down(struct phylink_config *config,
				 unsigned int mode, phy_interface_t interface)
{
	struct net_device *ndev = to_net_dev(config->dev);
	struct mvneta_port *pp = netdev_priv(ndev);
	u32 val;

	mvneta_port_down(pp);

	if (!phylink_autoneg_inband(mode)) {
		val = mvreg_read(pp, MVNETA_GMAC_AUTONEG_CONFIG);
		val &= ~MVNETA_GMAC_FORCE_LINK_PASS;
		val |= MVNETA_GMAC_FORCE_LINK_DOWN;
		mvreg_write(pp, MVNETA_GMAC_AUTONEG_CONFIG, val);
	}

	pp->eee_active = false;
	mvneta_set_eee(pp, false);
}