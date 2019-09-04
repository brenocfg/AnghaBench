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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rss_info {int /*<<< orphan*/  rss_hkey; int /*<<< orphan*/ * rss_queue; } ;
struct net_device {int dummy; } ;
struct be_adapter {struct rss_info rss_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  RSS_HASH_KEY_LEN ; 
 int RSS_INDIR_TABLE_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_get_rxfh(struct net_device *netdev, u32 *indir, u8 *hkey,
		       u8 *hfunc)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	int i;
	struct rss_info *rss = &adapter->rss_info;

	if (indir) {
		for (i = 0; i < RSS_INDIR_TABLE_LEN; i++)
			indir[i] = rss->rss_queue[i];
	}

	if (hkey)
		memcpy(hkey, rss->rss_hkey, RSS_HASH_KEY_LEN);

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	return 0;
}