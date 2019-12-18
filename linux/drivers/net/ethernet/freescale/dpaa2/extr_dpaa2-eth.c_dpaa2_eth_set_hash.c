#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct net_device {int dummy; } ;
struct dpaa2_eth_priv {int dummy; } ;
struct TYPE_3__ {int rxnfc_field; int id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_DIST_HASH ; 
 int EOPNOTSUPP ; 
 TYPE_1__* dist_fields ; 
 int /*<<< orphan*/  dpaa2_eth_hash_enabled (struct dpaa2_eth_priv*) ; 
 int dpaa2_eth_set_dist_key (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 

int dpaa2_eth_set_hash(struct net_device *net_dev, u64 flags)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u64 key = 0;
	int i;

	if (!dpaa2_eth_hash_enabled(priv))
		return -EOPNOTSUPP;

	for (i = 0; i < ARRAY_SIZE(dist_fields); i++)
		if (dist_fields[i].rxnfc_field & flags)
			key |= dist_fields[i].id;

	return dpaa2_eth_set_dist_key(net_dev, DPAA2_ETH_RX_DIST_HASH, key);
}