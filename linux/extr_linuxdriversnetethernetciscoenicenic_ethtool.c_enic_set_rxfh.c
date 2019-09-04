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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct enic {int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENIC_RSS_LEN ; 
 scalar_t__ const ETH_RSS_HASH_NO_CHANGE ; 
 scalar_t__ const ETH_RSS_HASH_TOP ; 
 int __enic_set_rsskey (struct enic*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_set_rxfh(struct net_device *netdev, const u32 *indir,
			 const u8 *hkey, const u8 hfunc)
{
	struct enic *enic = netdev_priv(netdev);

	if ((hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP) ||
	    indir)
		return -EINVAL;

	if (hkey)
		memcpy(enic->rss_key, hkey, ENIC_RSS_LEN);

	return __enic_set_rsskey(enic);
}