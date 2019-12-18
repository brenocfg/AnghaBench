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
struct virtnet_info {int /*<<< orphan*/  max_queue_pairs; int /*<<< orphan*/  curr_queue_pairs; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {scalar_t__ other_count; scalar_t__ tx_count; scalar_t__ rx_count; scalar_t__ max_other; int /*<<< orphan*/  max_combined; int /*<<< orphan*/  combined_count; } ;

/* Variables and functions */
 struct virtnet_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void virtnet_get_channels(struct net_device *dev,
				 struct ethtool_channels *channels)
{
	struct virtnet_info *vi = netdev_priv(dev);

	channels->combined_count = vi->curr_queue_pairs;
	channels->max_combined = vi->max_queue_pairs;
	channels->max_other = 0;
	channels->rx_count = 0;
	channels->tx_count = 0;
	channels->other_count = 0;
}