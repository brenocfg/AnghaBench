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
struct skb_info {int /*<<< orphan*/  internal_hdr_size; } ;
struct sk_buff {int dummy; } ;
struct rsi_hw {int /*<<< orphan*/  hw; } ;
struct ieee80211_tx_info {scalar_t__ driver_data; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_INFO_DRIVER_DATA_SIZE ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

void rsi_indicate_tx_status(struct rsi_hw *adapter,
			    struct sk_buff *skb,
			    int status)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct skb_info *tx_params;

	if (!adapter->hw) {
		rsi_dbg(ERR_ZONE, "##### No MAC #####\n");
		return;
	}

	if (!status)
		info->flags |= IEEE80211_TX_STAT_ACK;

	tx_params = (struct skb_info *)info->driver_data;
	skb_pull(skb, tx_params->internal_hdr_size);
	memset(info->driver_data, 0, IEEE80211_TX_INFO_DRIVER_DATA_SIZE);

	ieee80211_tx_status_irqsafe(adapter->hw, skb);
}