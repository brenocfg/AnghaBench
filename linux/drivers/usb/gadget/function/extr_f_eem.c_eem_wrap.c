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
typedef  int u16 ;
struct usb_ep {int maxpacket; } ;
struct sk_buff {int len; } ;
struct gether {struct usb_ep* in_ep; } ;

/* Variables and functions */
 int EEM_HLEN ; 
 int ETH_FCS_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *eem_wrap(struct gether *port, struct sk_buff *skb)
{
	struct sk_buff	*skb2 = NULL;
	struct usb_ep	*in = port->in_ep;
	int		headroom, tailroom, padlen = 0;
	u16		len;

	if (!skb)
		return NULL;

	len = skb->len;
	headroom = skb_headroom(skb);
	tailroom = skb_tailroom(skb);

	/* When (len + EEM_HLEN + ETH_FCS_LEN) % in->maxpacket) is 0,
	 * stick two bytes of zero-length EEM packet on the end.
	 */
	if (((len + EEM_HLEN + ETH_FCS_LEN) % in->maxpacket) == 0)
		padlen += 2;

	if ((tailroom >= (ETH_FCS_LEN + padlen)) &&
			(headroom >= EEM_HLEN) && !skb_cloned(skb))
		goto done;

	skb2 = skb_copy_expand(skb, EEM_HLEN, ETH_FCS_LEN + padlen, GFP_ATOMIC);
	dev_kfree_skb_any(skb);
	skb = skb2;
	if (!skb)
		return skb;

done:
	/* use the "no CRC" option */
	put_unaligned_be32(0xdeadbeef, skb_put(skb, 4));

	/* EEM packet header format:
	 * b0..13:	length of ethernet frame
	 * b14:		bmCRC (0 == sentinel CRC)
	 * b15:		bmType (0 == data)
	 */
	len = skb->len;
	put_unaligned_le16(len & 0x3FFF, skb_push(skb, 2));

	/* add a zero-length EEM packet, if needed */
	if (padlen)
		put_unaligned_le16(0, skb_put(skb, 2));

	return skb;
}