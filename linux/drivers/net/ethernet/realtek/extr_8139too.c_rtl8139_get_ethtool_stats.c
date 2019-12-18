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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_lost_in_ring; int /*<<< orphan*/  tx_timeouts; int /*<<< orphan*/  tx_buf_mapped; int /*<<< orphan*/  early_rx; } ;
struct rtl8139_private {TYPE_1__ xstats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 struct rtl8139_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void rtl8139_get_ethtool_stats(struct net_device *dev, struct ethtool_stats *stats, u64 *data)
{
	struct rtl8139_private *tp = netdev_priv(dev);

	data[0] = tp->xstats.early_rx;
	data[1] = tp->xstats.tx_buf_mapped;
	data[2] = tp->xstats.tx_timeouts;
	data[3] = tp->xstats.rx_lost_in_ring;
}