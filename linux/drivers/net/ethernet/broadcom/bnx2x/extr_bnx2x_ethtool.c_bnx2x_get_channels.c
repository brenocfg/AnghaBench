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
struct ethtool_channels {int /*<<< orphan*/  combined_count; int /*<<< orphan*/  max_combined; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MAX_RSS_COUNT (struct bnx2x*) ; 
 int /*<<< orphan*/  BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bnx2x_get_channels(struct net_device *dev,
			       struct ethtool_channels *channels)
{
	struct bnx2x *bp = netdev_priv(dev);

	channels->max_combined = BNX2X_MAX_RSS_COUNT(bp);
	channels->combined_count = BNX2X_NUM_ETH_QUEUES(bp);
}