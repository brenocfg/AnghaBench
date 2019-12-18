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
struct sk_buff {scalar_t__ data; } ;
struct il_priv {int /*<<< orphan*/  hw; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  il4965_non_agg_tx_status (struct il_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il4965_tx_status(struct il_priv *il, struct sk_buff *skb, bool is_agg)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;

	if (!is_agg)
		il4965_non_agg_tx_status(il, hdr->addr1);

	ieee80211_tx_status_irqsafe(il->hw, skb);
}