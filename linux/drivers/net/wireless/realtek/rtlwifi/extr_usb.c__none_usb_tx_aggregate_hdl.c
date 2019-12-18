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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 

__attribute__((used)) static struct sk_buff *_none_usb_tx_aggregate_hdl(struct ieee80211_hw *hw,
						  struct sk_buff_head *list)
{
	return skb_dequeue(list);
}