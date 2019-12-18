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
struct TYPE_2__ {int /*<<< orphan*/  asp; int /*<<< orphan*/  rmon; } ;
struct stmmac_priv {int /*<<< orphan*/  sstats; TYPE_1__ dma_cap; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int STMMAC_MMC_STATS_LEN ; 
 int STMMAC_SAFETY_FEAT_SIZE ; 
 int STMMAC_STATS_LEN ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_safety_feat_dump (struct stmmac_priv*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stmmac_selftest_get_count (struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_get_sset_count(struct net_device *netdev, int sset)
{
	struct stmmac_priv *priv = netdev_priv(netdev);
	int i, len, safety_len = 0;

	switch (sset) {
	case ETH_SS_STATS:
		len = STMMAC_STATS_LEN;

		if (priv->dma_cap.rmon)
			len += STMMAC_MMC_STATS_LEN;
		if (priv->dma_cap.asp) {
			for (i = 0; i < STMMAC_SAFETY_FEAT_SIZE; i++) {
				if (!stmmac_safety_feat_dump(priv,
							&priv->sstats, i,
							NULL, NULL))
					safety_len++;
			}

			len += safety_len;
		}

		return len;
	case ETH_SS_TEST:
		return stmmac_selftest_get_count(priv);
	default:
		return -EOPNOTSUPP;
	}
}