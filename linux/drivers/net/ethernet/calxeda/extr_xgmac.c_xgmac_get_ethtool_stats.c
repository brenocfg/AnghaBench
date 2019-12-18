#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xgmac_priv {int base; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {int stat_offset; scalar_t__ is_reg; } ;

/* Variables and functions */
 int XGMAC_STATS_LEN ; 
 struct xgmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (int) ; 
 TYPE_1__* xgmac_gstrings_stats ; 

__attribute__((used)) static void xgmac_get_ethtool_stats(struct net_device *dev,
					 struct ethtool_stats *dummy,
					 u64 *data)
{
	struct xgmac_priv *priv = netdev_priv(dev);
	void *p = priv;
	int i;

	for (i = 0; i < XGMAC_STATS_LEN; i++) {
		if (xgmac_gstrings_stats[i].is_reg)
			*data++ = readl(priv->base +
				xgmac_gstrings_stats[i].stat_offset);
		else
			*data++ = *(u32 *)(p +
				xgmac_gstrings_stats[i].stat_offset);
	}
}