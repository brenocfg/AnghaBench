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
struct sk_buff {int len; unsigned char* data; scalar_t__ mac_len; } ;

/* Variables and functions */
 unsigned char DLE_FLAG ; 
 unsigned char bitrev8 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,unsigned char) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *iraw_encode(struct sk_buff *skb)
{
	struct sk_buff *iraw_skb;
	unsigned char c;
	unsigned char *cp;
	int len;

	/* size of new buffer (worst case = every byte must be stuffed):
	 * 2 * original size + room for link layer header
	 */
	iraw_skb = dev_alloc_skb(2 * skb->len + skb->mac_len);
	if (!iraw_skb) {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	/* copy link layer header into new skb */
	skb_reset_mac_header(iraw_skb);
	skb_reserve(iraw_skb, skb->mac_len);
	memcpy(skb_mac_header(iraw_skb), skb_mac_header(skb), skb->mac_len);
	iraw_skb->mac_len = skb->mac_len;

	/* copy and stuff data */
	cp = skb->data;
	len = skb->len;
	while (len--) {
		c = bitrev8(*cp++);
		if (c == DLE_FLAG)
			skb_put_u8(iraw_skb, c);
		skb_put_u8(iraw_skb, c);
	}
	dev_kfree_skb_any(skb);
	return iraw_skb;
}