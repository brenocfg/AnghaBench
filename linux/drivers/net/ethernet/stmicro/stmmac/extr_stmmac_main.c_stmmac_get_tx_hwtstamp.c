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
struct stmmac_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  hw; int /*<<< orphan*/  adv_ts; int /*<<< orphan*/  hwts_tx_en; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct dma_desc {int dummy; } ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int SKBTX_IN_PROGRESS ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  stmmac_get_mac_tx_timestamp (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_get_timestamp (struct stmmac_priv*,struct dma_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stmmac_get_tx_timestamp_status (struct stmmac_priv*,struct dma_desc*) ; 

__attribute__((used)) static void stmmac_get_tx_hwtstamp(struct stmmac_priv *priv,
				   struct dma_desc *p, struct sk_buff *skb)
{
	struct skb_shared_hwtstamps shhwtstamp;
	bool found = false;
	u64 ns = 0;

	if (!priv->hwts_tx_en)
		return;

	/* exit if skb doesn't support hw tstamp */
	if (likely(!skb || !(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)))
		return;

	/* check tx tstamp status */
	if (stmmac_get_tx_timestamp_status(priv, p)) {
		stmmac_get_timestamp(priv, p, priv->adv_ts, &ns);
		found = true;
	} else if (!stmmac_get_mac_tx_timestamp(priv, priv->hw, &ns)) {
		found = true;
	}

	if (found) {
		memset(&shhwtstamp, 0, sizeof(struct skb_shared_hwtstamps));
		shhwtstamp.hwtstamp = ns_to_ktime(ns);

		netdev_dbg(priv->dev, "get valid TX hw timestamp %llu\n", ns);
		/* pass tstamp to stack */
		skb_tstamp_tx(skb, &shhwtstamp);
	}
}