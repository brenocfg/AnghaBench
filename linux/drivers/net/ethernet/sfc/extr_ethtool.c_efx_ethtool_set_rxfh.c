#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__* rx_hash_key; int /*<<< orphan*/ * rx_indir_table; } ;
struct efx_nic {TYPE_2__* type; TYPE_1__ rss_context; } ;
struct TYPE_4__ {int (* rx_push_rss_config ) (struct efx_nic*,int,int /*<<< orphan*/  const*,scalar_t__ const*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct efx_nic*,int,int /*<<< orphan*/  const*,scalar_t__ const*) ; 

__attribute__((used)) static int efx_ethtool_set_rxfh(struct net_device *net_dev, const u32 *indir,
				const u8 *key, const u8 hfunc)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	/* Hash function is Toeplitz, cannot be changed */
	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;
	if (!indir && !key)
		return 0;

	if (!key)
		key = efx->rss_context.rx_hash_key;
	if (!indir)
		indir = efx->rss_context.rx_indir_table;

	return efx->type->rx_push_rss_config(efx, true, indir, key);
}