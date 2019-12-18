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
typedef  size_t u8 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 size_t IEEE80211_AC_BE ; 
 size_t RTW_TX_QUEUE_BCN ; 
 size_t RTW_TX_QUEUE_MGMT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 size_t* ac_to_hwq ; 
 int ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u8 rtw_hw_queue_mapping(struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;
	u8 q_mapping = skb_get_queue_mapping(skb);
	u8 queue;

	if (unlikely(ieee80211_is_beacon(fc)))
		queue = RTW_TX_QUEUE_BCN;
	else if (unlikely(ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc)))
		queue = RTW_TX_QUEUE_MGMT;
	else if (WARN_ON_ONCE(q_mapping >= ARRAY_SIZE(ac_to_hwq)))
		queue = ac_to_hwq[IEEE80211_AC_BE];
	else
		queue = ac_to_hwq[q_mapping];

	return queue;
}