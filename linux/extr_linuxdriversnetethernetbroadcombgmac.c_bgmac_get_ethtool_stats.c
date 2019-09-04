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
typedef  int uint64_t ;
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct bgmac_stat {int size; scalar_t__ offset; } ;
struct bgmac {int dummy; } ;

/* Variables and functions */
 unsigned int BGMAC_STATS_LEN ; 
 struct bgmac_stat* bgmac_get_strings_stats ; 
 int bgmac_read (struct bgmac*,scalar_t__) ; 
 struct bgmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static void bgmac_get_ethtool_stats(struct net_device *dev,
				    struct ethtool_stats *ss, uint64_t *data)
{
	struct bgmac *bgmac = netdev_priv(dev);
	const struct bgmac_stat *s;
	unsigned int i;
	u64 val;

	if (!netif_running(dev))
		return;

	for (i = 0; i < BGMAC_STATS_LEN; i++) {
		s = &bgmac_get_strings_stats[i];
		val = 0;
		if (s->size == 8)
			val = (u64)bgmac_read(bgmac, s->offset + 4) << 32;
		val |= bgmac_read(bgmac, s->offset);
		data[i] = val;
	}
}