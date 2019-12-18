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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; scalar_t__ autoneg; } ;
struct TYPE_2__ {int flow_control; } ;
struct aq_nic_s {TYPE_1__ aq_nic_cfg; } ;

/* Variables and functions */
 int AQ_NIC_FC_RX ; 
 int AQ_NIC_FC_TX ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void aq_ethtool_get_pauseparam(struct net_device *ndev,
				      struct ethtool_pauseparam *pause)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	u32 fc = aq_nic->aq_nic_cfg.flow_control;

	pause->autoneg = 0;

	pause->rx_pause = !!(fc & AQ_NIC_FC_RX);
	pause->tx_pause = !!(fc & AQ_NIC_FC_TX);

}