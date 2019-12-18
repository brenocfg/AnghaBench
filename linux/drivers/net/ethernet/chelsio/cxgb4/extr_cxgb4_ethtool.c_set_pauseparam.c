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
struct link_config {int pcaps; int /*<<< orphan*/  requested_fc; } ;
struct port_info {int /*<<< orphan*/  tx_chan; TYPE_1__* adapter; struct link_config link_cfg; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 int EINVAL ; 
 int FW_PORT_CAP32_ANEG ; 
 int /*<<< orphan*/  PAUSE_AUTONEG ; 
 int /*<<< orphan*/  PAUSE_RX ; 
 int /*<<< orphan*/  PAUSE_TX ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int t4_link_l1cfg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link_config*) ; 

__attribute__((used)) static int set_pauseparam(struct net_device *dev,
			  struct ethtool_pauseparam *epause)
{
	struct port_info *p = netdev_priv(dev);
	struct link_config *lc = &p->link_cfg;

	if (epause->autoneg == AUTONEG_DISABLE)
		lc->requested_fc = 0;
	else if (lc->pcaps & FW_PORT_CAP32_ANEG)
		lc->requested_fc = PAUSE_AUTONEG;
	else
		return -EINVAL;

	if (epause->rx_pause)
		lc->requested_fc |= PAUSE_RX;
	if (epause->tx_pause)
		lc->requested_fc |= PAUSE_TX;
	if (netif_running(dev))
		return t4_link_l1cfg(p->adapter, p->adapter->mbox, p->tx_chan,
				     lc);
	return 0;
}