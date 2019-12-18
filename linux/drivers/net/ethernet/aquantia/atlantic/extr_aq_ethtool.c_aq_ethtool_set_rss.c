#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  unsigned int u32 ;
struct net_device {int dummy; } ;
struct aq_nic_s {int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; } ;
struct TYPE_5__ {unsigned int indirection_table_size; unsigned int* indirection_table; int /*<<< orphan*/  hash_secret_key; } ;
struct aq_nic_cfg_s {TYPE_2__ aq_rss; } ;
struct TYPE_4__ {int (* hw_rss_hash_set ) (int /*<<< orphan*/ ,TYPE_2__*) ;int (* hw_rss_set ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 struct aq_nic_cfg_s* aq_nic_get_cfg (struct aq_nic_s*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int aq_ethtool_set_rss(struct net_device *netdev, const u32 *indir,
			      const u8 *key, const u8 hfunc)
{
	struct aq_nic_s *aq_nic = netdev_priv(netdev);
	struct aq_nic_cfg_s *cfg;
	unsigned int i = 0U;
	u32 rss_entries;
	int err = 0;

	cfg = aq_nic_get_cfg(aq_nic);
	rss_entries = cfg->aq_rss.indirection_table_size;

	/* We do not allow change in unsupported parameters */
	if (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		return -EOPNOTSUPP;
	/* Fill out the redirection table */
	if (indir)
		for (i = 0; i < rss_entries; i++)
			cfg->aq_rss.indirection_table[i] = indir[i];

	/* Fill out the rss hash key */
	if (key) {
		memcpy(cfg->aq_rss.hash_secret_key, key,
		       sizeof(cfg->aq_rss.hash_secret_key));
		err = aq_nic->aq_hw_ops->hw_rss_hash_set(aq_nic->aq_hw,
			&cfg->aq_rss);
		if (err)
			return err;
	}

	err = aq_nic->aq_hw_ops->hw_rss_set(aq_nic->aq_hw, &cfg->aq_rss);

	return err;
}