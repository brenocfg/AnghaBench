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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ef4_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int (* rx_push_rss_config ) (struct ef4_nic*,int,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct ef4_nic*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ef4_ethtool_set_rxfh(struct net_device *net_dev, const u32 *indir,
				const u8 *key, const u8 hfunc)
{
	struct ef4_nic *efx = netdev_priv(net_dev);

	/* We do not allow change in unsupported parameters */
	if (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		return -EOPNOTSUPP;
	if (!indir)
		return 0;

	return efx->type->rx_push_rss_config(efx, true, indir);
}