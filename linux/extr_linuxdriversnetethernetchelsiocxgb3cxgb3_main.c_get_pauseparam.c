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
struct TYPE_2__ {int requested_fc; int fc; } ;
struct port_info {TYPE_1__ link_config; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; } ;

/* Variables and functions */
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void get_pauseparam(struct net_device *dev,
			   struct ethtool_pauseparam *epause)
{
	struct port_info *p = netdev_priv(dev);

	epause->autoneg = (p->link_config.requested_fc & PAUSE_AUTONEG) != 0;
	epause->rx_pause = (p->link_config.fc & PAUSE_RX) != 0;
	epause->tx_pause = (p->link_config.fc & PAUSE_TX) != 0;
}