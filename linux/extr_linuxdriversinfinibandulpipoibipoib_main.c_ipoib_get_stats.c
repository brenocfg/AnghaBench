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
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int /*<<< orphan*/  stats; } ;
struct ipoib_dev_priv {TYPE_1__* rn_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_get_stats64 ) (struct net_device*,struct rtnl_link_stats64*) ;} ;

/* Variables and functions */
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_stats_to_stats64 (struct rtnl_link_stats64*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct rtnl_link_stats64*) ; 

__attribute__((used)) static void ipoib_get_stats(struct net_device *dev,
			    struct rtnl_link_stats64 *stats)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	if (priv->rn_ops->ndo_get_stats64)
		priv->rn_ops->ndo_get_stats64(dev, stats);
	else
		netdev_stats_to_stats64(stats, &dev->stats);
}