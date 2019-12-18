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
struct rmnet_priv_stats {int dummy; } ;
struct rmnet_priv {struct rmnet_priv_stats stats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct rmnet_priv_stats*,int) ; 
 struct rmnet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_gstrings_stats ; 

__attribute__((used)) static void rmnet_get_ethtool_stats(struct net_device *dev,
				    struct ethtool_stats *stats, u64 *data)
{
	struct rmnet_priv *priv = netdev_priv(dev);
	struct rmnet_priv_stats *st = &priv->stats;

	if (!data)
		return;

	memcpy(data, st, ARRAY_SIZE(rmnet_gstrings_stats) * sizeof(u64));
}