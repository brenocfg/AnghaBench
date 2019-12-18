#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ionic_lif {TYPE_4__* ionic; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; scalar_t__ autoneg; } ;
struct TYPE_7__ {TYPE_2__* port_info; } ;
struct TYPE_8__ {TYPE_3__ idev; } ;
struct TYPE_5__ {int pause_type; } ;
struct TYPE_6__ {TYPE_1__ config; } ;

/* Variables and functions */
 int IONIC_PAUSE_F_RX ; 
 int IONIC_PAUSE_F_TX ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ionic_get_pauseparam(struct net_device *netdev,
				 struct ethtool_pauseparam *pause)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	u8 pause_type;

	pause->autoneg = 0;

	pause_type = lif->ionic->idev.port_info->config.pause_type;
	if (pause_type) {
		pause->rx_pause = pause_type & IONIC_PAUSE_F_RX ? 1 : 0;
		pause->tx_pause = pause_type & IONIC_PAUSE_F_TX ? 1 : 0;
	}
}