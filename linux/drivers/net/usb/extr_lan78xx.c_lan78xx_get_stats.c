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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  access_lock; int /*<<< orphan*/  curr_stat; } ;
struct lan78xx_net {TYPE_1__ stats; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan78xx_update_stats (struct lan78xx_net*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void lan78xx_get_stats(struct net_device *netdev,
			      struct ethtool_stats *stats, u64 *data)
{
	struct lan78xx_net *dev = netdev_priv(netdev);

	lan78xx_update_stats(dev);

	mutex_lock(&dev->stats.access_lock);
	memcpy(data, &dev->stats.curr_stat, sizeof(dev->stats.curr_stat));
	mutex_unlock(&dev->stats.access_lock);
}