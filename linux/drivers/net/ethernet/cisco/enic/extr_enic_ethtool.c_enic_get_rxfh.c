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
struct net_device {int dummy; } ;
struct enic {int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENIC_RSS_LEN ; 
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_get_rxfh(struct net_device *netdev, u32 *indir, u8 *hkey,
			 u8 *hfunc)
{
	struct enic *enic = netdev_priv(netdev);

	if (hkey)
		memcpy(hkey, enic->rss_key, ENIC_RSS_LEN);

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	return 0;
}