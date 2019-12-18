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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct rndis_device {scalar_t__* rx_table; scalar_t__* rss_key; } ;
struct netvsc_device {scalar_t__ const num_chn; struct rndis_device* extension; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int ITAB_NUM ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int rndis_filter_set_rss_param (struct rndis_device*,scalar_t__ const*) ; 
 struct netvsc_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_set_rxfh(struct net_device *dev, const u32 *indir,
			   const u8 *key, const u8 hfunc)
{
	struct net_device_context *ndc = netdev_priv(dev);
	struct netvsc_device *ndev = rtnl_dereference(ndc->nvdev);
	struct rndis_device *rndis_dev;
	int i;

	if (!ndev)
		return -ENODEV;

	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;

	rndis_dev = ndev->extension;
	if (indir) {
		for (i = 0; i < ITAB_NUM; i++)
			if (indir[i] >= ndev->num_chn)
				return -EINVAL;

		for (i = 0; i < ITAB_NUM; i++)
			rndis_dev->rx_table[i] = indir[i];
	}

	if (!key) {
		if (!indir)
			return 0;

		key = rndis_dev->rss_key;
	}

	return rndis_filter_set_rss_param(rndis_dev, key);
}