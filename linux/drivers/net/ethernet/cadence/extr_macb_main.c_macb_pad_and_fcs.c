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
typedef  int u32 ;
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  data; int /*<<< orphan*/  head; } ;
struct net_device {int features; } ;
struct TYPE_2__ {scalar_t__ gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int ENOMEM ; 
 int ETH_FCS_LEN ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETIF_F_HW_CSUM ; 
 int crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_header_cloned (struct sk_buff*) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int macb_pad_and_fcs(struct sk_buff **skb, struct net_device *ndev)
{
	bool cloned = skb_cloned(*skb) || skb_header_cloned(*skb);
	int padlen = ETH_ZLEN - (*skb)->len;
	int headroom = skb_headroom(*skb);
	int tailroom = skb_tailroom(*skb);
	struct sk_buff *nskb;
	u32 fcs;

	if (!(ndev->features & NETIF_F_HW_CSUM) ||
	    !((*skb)->ip_summed != CHECKSUM_PARTIAL) ||
	    skb_shinfo(*skb)->gso_size)	/* Not available for GSO */
		return 0;

	if (padlen <= 0) {
		/* FCS could be appeded to tailroom. */
		if (tailroom >= ETH_FCS_LEN)
			goto add_fcs;
		/* FCS could be appeded by moving data to headroom. */
		else if (!cloned && headroom + tailroom >= ETH_FCS_LEN)
			padlen = 0;
		/* No room for FCS, need to reallocate skb. */
		else
			padlen = ETH_FCS_LEN;
	} else {
		/* Add room for FCS. */
		padlen += ETH_FCS_LEN;
	}

	if (!cloned && headroom + tailroom >= padlen) {
		(*skb)->data = memmove((*skb)->head, (*skb)->data, (*skb)->len);
		skb_set_tail_pointer(*skb, (*skb)->len);
	} else {
		nskb = skb_copy_expand(*skb, 0, padlen, GFP_ATOMIC);
		if (!nskb)
			return -ENOMEM;

		dev_consume_skb_any(*skb);
		*skb = nskb;
	}

	if (padlen > ETH_FCS_LEN)
		skb_put_zero(*skb, padlen - ETH_FCS_LEN);

add_fcs:
	/* set FCS to packet */
	fcs = crc32_le(~0, (*skb)->data, (*skb)->len);
	fcs = ~fcs;

	skb_put_u8(*skb, fcs		& 0xff);
	skb_put_u8(*skb, (fcs >> 8)	& 0xff);
	skb_put_u8(*skb, (fcs >> 16)	& 0xff);
	skb_put_u8(*skb, (fcs >> 24)	& 0xff);

	return 0;
}