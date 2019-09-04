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
struct net_device {int dummy; } ;
struct mvpp2_port {scalar_t__ phy_interface; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MVPP2_GMAC_AUTONEG_CONFIG ; 
 int MVPP2_GMAC_IN_BAND_AUTONEG ; 
 int MVPP2_GMAC_IN_BAND_RESTART_AN ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mvpp2_mac_an_restart(struct net_device *dev)
{
	struct mvpp2_port *port = netdev_priv(dev);
	u32 val;

	if (port->phy_interface != PHY_INTERFACE_MODE_SGMII)
		return;

	val = readl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);
	/* The RESTART_AN bit is cleared by the h/w after restarting the AN
	 * process.
	 */
	val |= MVPP2_GMAC_IN_BAND_RESTART_AN | MVPP2_GMAC_IN_BAND_AUTONEG;
	writel(val, port->base + MVPP2_GMAC_AUTONEG_CONFIG);
}