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
typedef  void ieee80211_hdr ;
struct _carl9170_tx_superframe {scalar_t__ frame_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ieee80211_hdr *carl9170_get_hdr(struct sk_buff *skb)
{
	return (void *)((struct _carl9170_tx_superframe *)
		skb->data)->frame_data;
}