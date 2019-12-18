#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_1__* net; int /*<<< orphan*/  data; } ;
struct sk_buff {scalar_t__ len; int* data; void* protocol; TYPE_1__* dev; } ;
struct qmi_wwan_state {int flags; } ;
typedef  void* __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; void* h_proto; } ;
struct TYPE_3__ {scalar_t__ hard_header_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int QMI_WWAN_FLAG_MUX ; 
 int QMI_WWAN_FLAG_RAWIP ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qmimux_rx_fixup (struct usbnet*,struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int qmi_wwan_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	struct qmi_wwan_state *info = (void *)&dev->data;
	bool rawip = info->flags & QMI_WWAN_FLAG_RAWIP;
	__be16 proto;

	/* This check is no longer done by usbnet */
	if (skb->len < dev->net->hard_header_len)
		return 0;

	if (info->flags & QMI_WWAN_FLAG_MUX)
		return qmimux_rx_fixup(dev, skb);

	switch (skb->data[0] & 0xf0) {
	case 0x40:
		proto = htons(ETH_P_IP);
		break;
	case 0x60:
		proto = htons(ETH_P_IPV6);
		break;
	case 0x00:
		if (rawip)
			return 0;
		if (is_multicast_ether_addr(skb->data))
			return 1;
		/* possibly bogus destination - rewrite just in case */
		skb_reset_mac_header(skb);
		goto fix_dest;
	default:
		if (rawip)
			return 0;
		/* pass along other packets without modifications */
		return 1;
	}
	if (rawip) {
		skb_reset_mac_header(skb);
		skb->dev = dev->net; /* normally set by eth_type_trans */
		skb->protocol = proto;
		return 1;
	}

	if (skb_headroom(skb) < ETH_HLEN)
		return 0;
	skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	eth_hdr(skb)->h_proto = proto;
	eth_zero_addr(eth_hdr(skb)->h_source);
fix_dest:
	memcpy(eth_hdr(skb)->h_dest, dev->net->dev_addr, ETH_ALEN);
	return 1;
}