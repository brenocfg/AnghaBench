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
struct ieee80211_tx_info {int flags; } ;
struct ar9170 {int /*<<< orphan*/  usb_tasklet; int /*<<< orphan*/  tx_ampdu_upload; int /*<<< orphan*/  tx_total_pending; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ carl9170_tx_put_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void carl9170_tx_callback(struct ar9170 *ar, struct sk_buff *skb)
{
	struct ieee80211_tx_info *txinfo = IEEE80211_SKB_CB(skb);

	atomic_dec(&ar->tx_total_pending);

	if (txinfo->flags & IEEE80211_TX_CTL_AMPDU)
		atomic_dec(&ar->tx_ampdu_upload);

	if (carl9170_tx_put_skb(skb))
		tasklet_hi_schedule(&ar->usb_tasklet);
}