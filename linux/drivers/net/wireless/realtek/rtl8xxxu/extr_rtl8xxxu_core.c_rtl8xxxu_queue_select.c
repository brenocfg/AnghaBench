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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXDESC_QUEUE_MGNT ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_80211_to_rtl_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 

__attribute__((used)) static u32 rtl8xxxu_queue_select(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	u32 queue;

	if (ieee80211_is_mgmt(hdr->frame_control))
		queue = TXDESC_QUEUE_MGNT;
	else
		queue = rtl8xxxu_80211_to_rtl_queue(skb_get_queue_mapping(skb));

	return queue;
}