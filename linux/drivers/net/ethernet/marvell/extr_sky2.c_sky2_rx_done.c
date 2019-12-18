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
struct TYPE_2__ {int /*<<< orphan*/  syncp; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct sky2_port {int /*<<< orphan*/  last_rx; TYPE_1__ rx_stats; } ;
struct sky2_hw {struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int /*<<< orphan*/  sky2_rx_update (struct sky2_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sky2_rx_done(struct sky2_hw *hw, unsigned port,
				unsigned packets, unsigned bytes)
{
	struct net_device *dev = hw->dev[port];
	struct sky2_port *sky2 = netdev_priv(dev);

	if (packets == 0)
		return;

	u64_stats_update_begin(&sky2->rx_stats.syncp);
	sky2->rx_stats.packets += packets;
	sky2->rx_stats.bytes += bytes;
	u64_stats_update_end(&sky2->rx_stats.syncp);

	sky2->last_rx = jiffies;
	sky2_rx_update(netdev_priv(dev), rxqaddr[port]);
}