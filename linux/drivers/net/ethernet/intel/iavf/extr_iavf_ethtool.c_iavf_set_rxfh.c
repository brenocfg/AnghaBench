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
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct iavf_adapter {size_t rss_lut_size; scalar_t__* rss_lut; int /*<<< orphan*/  rss_key_size; int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int iavf_config_rss (struct iavf_adapter*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int iavf_set_rxfh(struct net_device *netdev, const u32 *indir,
			 const u8 *key, const u8 hfunc)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);
	u16 i;

	/* We do not allow change in unsupported parameters */
	if (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		return -EOPNOTSUPP;
	if (!indir)
		return 0;

	if (key)
		memcpy(adapter->rss_key, key, adapter->rss_key_size);

	/* Each 32 bits pointed by 'indir' is stored with a lut entry */
	for (i = 0; i < adapter->rss_lut_size; i++)
		adapter->rss_lut[i] = (u8)(indir[i]);

	return iavf_config_rss(adapter);
}