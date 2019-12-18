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
struct TYPE_2__ {int /*<<< orphan*/  tx_fc_en; int /*<<< orphan*/  rx_fc_en; } ;
union gmac_config0 {TYPE_1__ bits; int /*<<< orphan*/  bits32; } ;
struct net_device {int dummy; } ;
struct gemini_ethernet_port {scalar_t__ gmac_base; } ;
struct ethtool_pauseparam {int autoneg; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;

/* Variables and functions */
 scalar_t__ GMAC_CONFIG0 ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void gmac_get_pauseparam(struct net_device *netdev,
				struct ethtool_pauseparam *pparam)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	union gmac_config0 config0;

	config0.bits32 = readl(port->gmac_base + GMAC_CONFIG0);

	pparam->rx_pause = config0.bits.rx_fc_en;
	pparam->tx_pause = config0.bits.tx_fc_en;
	pparam->autoneg = true;
}