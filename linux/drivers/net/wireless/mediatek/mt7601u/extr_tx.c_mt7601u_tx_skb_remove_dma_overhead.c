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
struct sk_buff {int dummy; } ;
struct mt76_txwi {int dummy; } ;
struct TYPE_2__ {scalar_t__* status_driver_data; } ;
struct ieee80211_tx_info {TYPE_1__ status; } ;

/* Variables and functions */
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_remove_hdr_pad (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static void mt7601u_tx_skb_remove_dma_overhead(struct sk_buff *skb,
					       struct ieee80211_tx_info *info)
{
	int pkt_len = (unsigned long)info->status.status_driver_data[0];

	skb_pull(skb, sizeof(struct mt76_txwi) + 4);
	if (ieee80211_get_hdrlen_from_skb(skb) % 4)
		mt76_remove_hdr_pad(skb);

	skb_trim(skb, pkt_len);
}