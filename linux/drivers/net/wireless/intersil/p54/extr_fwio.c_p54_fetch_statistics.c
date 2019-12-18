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
struct sk_buff {int dummy; } ;
struct p54_tx_info {int extra_len; } ;
struct p54_statistics {int dummy; } ;
struct p54_common {int dummy; } ;
struct ieee80211_tx_info {scalar_t__ rate_driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  P54_CONTROL_TYPE_STAT_READBACK ; 
 int /*<<< orphan*/  P54_HDR_FLAG_CONTROL ; 
 struct sk_buff* p54_alloc_skb (struct p54_common*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_tx (struct p54_common*,struct sk_buff*) ; 

int p54_fetch_statistics(struct p54_common *priv)
{
	struct ieee80211_tx_info *txinfo;
	struct p54_tx_info *p54info;
	struct sk_buff *skb;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL,
			    sizeof(struct p54_statistics),
			    P54_CONTROL_TYPE_STAT_READBACK, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	/*
	 * The statistic feedback causes some extra headaches here, if it
	 * is not to crash/corrupt the firmware data structures.
	 *
	 * Unlike all other Control Get OIDs we can not use helpers like
	 * skb_put to reserve the space for the data we're requesting.
	 * Instead the extra frame length -which will hold the results later-
	 * will only be told to the p54_assign_address, so that following
	 * frames won't be placed into the  allegedly empty area.
	 */
	txinfo = IEEE80211_SKB_CB(skb);
	p54info = (void *) txinfo->rate_driver_data;
	p54info->extra_len = sizeof(struct p54_statistics);

	p54_tx(priv, skb);
	return 0;
}