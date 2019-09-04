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
struct xgbe_prv_data {int /*<<< orphan*/  rss_key; int /*<<< orphan*/ * rss_table; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMCH ; 
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  MAC_RSSDR ; 
 int /*<<< orphan*/  XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int xgbe_get_rxfh(struct net_device *netdev, u32 *indir, u8 *key,
			 u8 *hfunc)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	unsigned int i;

	if (indir) {
		for (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++)
			indir[i] = XGMAC_GET_BITS(pdata->rss_table[i],
						  MAC_RSSDR, DMCH);
	}

	if (key)
		memcpy(key, pdata->rss_key, sizeof(pdata->rss_key));

	if (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	return 0;
}