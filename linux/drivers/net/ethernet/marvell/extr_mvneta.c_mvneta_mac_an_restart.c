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
typedef  int u32 ;
struct phylink_config {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_GMAC_AUTONEG_CONFIG ; 
 int MVNETA_GMAC_INBAND_RESTART_AN ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 struct net_device* to_net_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_mac_an_restart(struct phylink_config *config)
{
	struct net_device *ndev = to_net_dev(config->dev);
	struct mvneta_port *pp = netdev_priv(ndev);
	u32 gmac_an = mvreg_read(pp, MVNETA_GMAC_AUTONEG_CONFIG);

	mvreg_write(pp, MVNETA_GMAC_AUTONEG_CONFIG,
		    gmac_an | MVNETA_GMAC_INBAND_RESTART_AN);
	mvreg_write(pp, MVNETA_GMAC_AUTONEG_CONFIG,
		    gmac_an & ~MVNETA_GMAC_INBAND_RESTART_AN);
}