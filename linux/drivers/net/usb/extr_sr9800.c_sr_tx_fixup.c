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
typedef  int u32 ;
struct usbnet {int maxpacket; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  padbytes ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,void*) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 void* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 void* skb_tail_pointer (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  usbnet_set_skb_tx_stats (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *sr_tx_fixup(struct usbnet *dev, struct sk_buff *skb,
					gfp_t flags)
{
	int headroom = skb_headroom(skb);
	int tailroom = skb_tailroom(skb);
	u32 padbytes = 0xffff0000;
	u32 packet_len;
	int padlen;
	void *ptr;

	padlen = ((skb->len + 4) % (dev->maxpacket - 1)) ? 0 : 4;

	if ((!skb_cloned(skb)) && ((headroom + tailroom) >= (4 + padlen))) {
		if ((headroom < 4) || (tailroom < padlen)) {
			skb->data = memmove(skb->head + 4, skb->data,
					    skb->len);
			skb_set_tail_pointer(skb, skb->len);
		}
	} else {
		struct sk_buff *skb2;
		skb2 = skb_copy_expand(skb, 4, padlen, flags);
		dev_kfree_skb_any(skb);
		skb = skb2;
		if (!skb)
			return NULL;
	}

	ptr = skb_push(skb, 4);
	packet_len = (((skb->len - 4) ^ 0x0000ffff) << 16) + (skb->len - 4);
	put_unaligned_le32(packet_len, ptr);

	if (padlen) {
		put_unaligned_le32(padbytes, skb_tail_pointer(skb));
		skb_put(skb, sizeof(padbytes));
	}

	usbnet_set_skb_tx_stats(skb, 1, 0);
	return skb;
}