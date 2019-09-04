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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct mvneta_port {int /*<<< orphan*/ * ethtool_stats; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_ethtool_update_stats (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_statistics ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mvneta_ethtool_get_stats(struct net_device *dev,
				     struct ethtool_stats *stats, u64 *data)
{
	struct mvneta_port *pp = netdev_priv(dev);
	int i;

	mvneta_ethtool_update_stats(pp);

	for (i = 0; i < ARRAY_SIZE(mvneta_statistics); i++)
		*data++ = pp->ethtool_stats[i];
}