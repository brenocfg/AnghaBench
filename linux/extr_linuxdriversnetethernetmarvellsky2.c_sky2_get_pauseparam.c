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
struct sky2_port {int flow_mode; int flags; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int tx_pause; int rx_pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
#define  FC_BOTH 131 
#define  FC_NONE 130 
#define  FC_RX 129 
#define  FC_TX 128 
 int SKY2_FLAG_AUTO_PAUSE ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void sky2_get_pauseparam(struct net_device *dev,
				struct ethtool_pauseparam *ecmd)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	switch (sky2->flow_mode) {
	case FC_NONE:
		ecmd->tx_pause = ecmd->rx_pause = 0;
		break;
	case FC_TX:
		ecmd->tx_pause = 1, ecmd->rx_pause = 0;
		break;
	case FC_RX:
		ecmd->tx_pause = 0, ecmd->rx_pause = 1;
		break;
	case FC_BOTH:
		ecmd->tx_pause = ecmd->rx_pause = 1;
	}

	ecmd->autoneg = (sky2->flags & SKY2_FLAG_AUTO_PAUSE)
		? AUTONEG_ENABLE : AUTONEG_DISABLE;
}