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
typedef  int u8 ;
typedef  int u16 ;
struct usbnet {TYPE_1__* net; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_proto; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int MBIM_IPS0_VID ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_neigh_solicit (struct usbnet*,int*,int) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_neigh_solicit (int*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int*,size_t) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *cdc_mbim_process_dgram(struct usbnet *dev, u8 *buf, size_t len, u16 tci)
{
	__be16 proto = htons(ETH_P_802_3);
	struct sk_buff *skb = NULL;

	if (tci < 256 || tci == MBIM_IPS0_VID) { /* IPS session? */
		if (len < sizeof(struct iphdr))
			goto err;

		switch (*buf & 0xf0) {
		case 0x40:
			proto = htons(ETH_P_IP);
			break;
		case 0x60:
			if (is_neigh_solicit(buf, len))
				do_neigh_solicit(dev, buf, tci);
			proto = htons(ETH_P_IPV6);
			break;
		default:
			goto err;
		}
	}

	skb = netdev_alloc_skb_ip_align(dev->net,  len + ETH_HLEN);
	if (!skb)
		goto err;

	/* add an ethernet header */
	skb_put(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	eth_hdr(skb)->h_proto = proto;
	eth_zero_addr(eth_hdr(skb)->h_source);
	memcpy(eth_hdr(skb)->h_dest, dev->net->dev_addr, ETH_ALEN);

	/* add datagram */
	skb_put_data(skb, buf, len);

	/* map MBIM session to VLAN */
	if (tci)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tci);
err:
	return skb;
}