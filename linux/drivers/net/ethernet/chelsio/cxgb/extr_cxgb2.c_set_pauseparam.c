#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct link_config {int requested_fc; int supported; scalar_t__ autoneg; int fc; } ;
struct port_info {TYPE_2__* mac; int /*<<< orphan*/  phy; struct link_config link_config; } ;
struct net_device {size_t if_port; struct adapter* ml_priv; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct adapter {struct port_info* port; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_speed_duplex_fc ) (TYPE_2__*,int,int,int) ;} ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int SUPPORTED_Autoneg ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  t1_link_start (int /*<<< orphan*/ ,TYPE_2__*,struct link_config*) ; 

__attribute__((used)) static int set_pauseparam(struct net_device *dev,
			  struct ethtool_pauseparam *epause)
{
	struct adapter *adapter = dev->ml_priv;
	struct port_info *p = &adapter->port[dev->if_port];
	struct link_config *lc = &p->link_config;

	if (epause->autoneg == AUTONEG_DISABLE)
		lc->requested_fc = 0;
	else if (lc->supported & SUPPORTED_Autoneg)
		lc->requested_fc = PAUSE_AUTONEG;
	else
		return -EINVAL;

	if (epause->rx_pause)
		lc->requested_fc |= PAUSE_RX;
	if (epause->tx_pause)
		lc->requested_fc |= PAUSE_TX;
	if (lc->autoneg == AUTONEG_ENABLE) {
		if (netif_running(dev))
			t1_link_start(p->phy, p->mac, lc);
	} else {
		lc->fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);
		if (netif_running(dev))
			p->mac->ops->set_speed_duplex_fc(p->mac, -1, -1,
							 lc->fc);
	}
	return 0;
}