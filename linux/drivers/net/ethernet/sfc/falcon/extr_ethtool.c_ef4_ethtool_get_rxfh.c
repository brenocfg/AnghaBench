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
struct ef4_nic {int /*<<< orphan*/  rx_indir_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ef4_ethtool_get_rxfh(struct net_device *net_dev, u32 *indir, u8 *key,
				u8 *hfunc)
{
	struct ef4_nic *efx = netdev_priv(net_dev);

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	if (indir)
		memcpy(indir, efx->rx_indir_table, sizeof(efx->rx_indir_table));
	return 0;
}