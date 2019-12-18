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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_WEP_ICV_LEN ; 
 int IEEE80211_WEP_IV_LEN ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int ath10k_htt_rx_frag_wep_decap(struct sk_buff *skb,
					u16 head_len,
					u16 hdr_len)
{
	u8 *orig_hdr;

	orig_hdr = skb->data;

	memmove(orig_hdr + IEEE80211_WEP_IV_LEN,
		orig_hdr, head_len + hdr_len);
	skb_pull(skb, IEEE80211_WEP_IV_LEN);
	skb_trim(skb, skb->len - IEEE80211_WEP_ICV_LEN);
	return 0;
}