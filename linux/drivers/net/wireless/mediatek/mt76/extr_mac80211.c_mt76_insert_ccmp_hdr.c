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
typedef  int u8 ;
struct sk_buff {int* data; scalar_t__ cb; } ;
struct mt76_rx_status {int* iv; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_FLAG_IV_STRIPPED ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

void mt76_insert_ccmp_hdr(struct sk_buff *skb, u8 key_id)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;
	int hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	u8 *hdr, *pn = status->iv;

	__skb_push(skb, 8);
	memmove(skb->data, skb->data + 8, hdr_len);
	hdr = skb->data + hdr_len;

	hdr[0] = pn[5];
	hdr[1] = pn[4];
	hdr[2] = 0;
	hdr[3] = 0x20 | (key_id << 6);
	hdr[4] = pn[3];
	hdr[5] = pn[2];
	hdr[6] = pn[1];
	hdr[7] = pn[0];

	status->flag &= ~RX_FLAG_IV_STRIPPED;
}