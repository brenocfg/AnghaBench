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
struct net_device {int dummy; } ;
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  combined_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_print_set_channels_input(struct net_device *netdev,
					  struct ethtool_channels *channels)
{
	netdev_err(netdev, "channel inputs: combined=%u, rx-only=%u, tx-only=%u\n",
		   channels->combined_count, channels->rx_count,
		   channels->tx_count);
}