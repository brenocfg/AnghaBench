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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nicvf_rss_info {int rss_size; int /*<<< orphan*/  key; int /*<<< orphan*/ * ind_tbl; int /*<<< orphan*/  enable; } ;
struct nicvf {int /*<<< orphan*/  netdev; struct nicvf_rss_info rss_info; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int RSS_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_config_rss (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_set_rss_key (struct nicvf*) ; 

__attribute__((used)) static int nicvf_set_rxfh(struct net_device *dev, const u32 *indir,
			  const u8 *hkey, const u8 hfunc)
{
	struct nicvf *nic = netdev_priv(dev);
	struct nicvf_rss_info *rss = &nic->rss_info;
	int idx;

	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;

	if (!rss->enable) {
		netdev_err(nic->netdev,
			   "RSS is disabled, cannot change settings\n");
		return -EIO;
	}

	if (indir) {
		for (idx = 0; idx < rss->rss_size; idx++)
			rss->ind_tbl[idx] = indir[idx];
	}

	if (hkey) {
		memcpy(rss->key, hkey, RSS_HASH_KEY_SIZE * sizeof(u64));
		nicvf_set_rss_key(nic);
	}

	nicvf_config_rss(nic);
	return 0;
}