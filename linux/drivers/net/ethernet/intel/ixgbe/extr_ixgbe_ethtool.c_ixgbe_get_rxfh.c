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
struct ixgbe_adapter {int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  ixgbe_get_reta (struct ixgbe_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_get_rxfh_key_size (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_get_rxfh(struct net_device *netdev, u32 *indir, u8 *key,
			  u8 *hfunc)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	if (indir)
		ixgbe_get_reta(adapter, indir);

	if (key)
		memcpy(key, adapter->rss_key, ixgbe_get_rxfh_key_size(netdev));

	return 0;
}