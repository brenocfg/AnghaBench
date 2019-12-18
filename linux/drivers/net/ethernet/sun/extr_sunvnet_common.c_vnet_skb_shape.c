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
struct sk_buff {int len; int data; scalar_t__ protocol; int csum_offset; scalar_t__ ip_summed; int /*<<< orphan*/  queue_mapping; int /*<<< orphan*/  dev; } ;
struct ipv6hdr {scalar_t__ nexthdr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct iphdr {scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  scalar_t__ __wsum ;
typedef  scalar_t__ __sum16 ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/  gso_type; int /*<<< orphan*/  gso_size; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int ETH_ZLEN ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int VNET_PACKET_SKIP ; 
 struct sk_buff* alloc_and_align_skb (int /*<<< orphan*/ ,int) ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 scalar_t__ csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int skb_checksum_start_offset (struct sk_buff*) ; 
 scalar_t__ skb_copy_and_csum_bits (struct sk_buff*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int,int) ; 
 int skb_frag_off (int /*<<< orphan*/ *) ; 
 int skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int skb_mac_header (struct sk_buff*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static inline struct sk_buff *vnet_skb_shape(struct sk_buff *skb, int ncookies)
{
	struct sk_buff *nskb;
	int i, len, pad, docopy;

	len = skb->len;
	pad = 0;
	if (len < ETH_ZLEN) {
		pad += ETH_ZLEN - skb->len;
		len += pad;
	}
	len += VNET_PACKET_SKIP;
	pad += 8 - (len & 7);

	/* make sure we have enough cookies and alignment in every frag */
	docopy = skb_shinfo(skb)->nr_frags >= ncookies;
	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];

		docopy |= skb_frag_off(f) & 7;
	}
	if (((unsigned long)skb->data & 7) != VNET_PACKET_SKIP ||
	    skb_tailroom(skb) < pad ||
	    skb_headroom(skb) < VNET_PACKET_SKIP || docopy) {
		int start = 0, offset;
		__wsum csum;

		len = skb->len > ETH_ZLEN ? skb->len : ETH_ZLEN;
		nskb = alloc_and_align_skb(skb->dev, len);
		if (!nskb) {
			dev_kfree_skb(skb);
			return NULL;
		}
		skb_reserve(nskb, VNET_PACKET_SKIP);

		nskb->protocol = skb->protocol;
		offset = skb_mac_header(skb) - skb->data;
		skb_set_mac_header(nskb, offset);
		offset = skb_network_header(skb) - skb->data;
		skb_set_network_header(nskb, offset);
		offset = skb_transport_header(skb) - skb->data;
		skb_set_transport_header(nskb, offset);

		offset = 0;
		nskb->csum_offset = skb->csum_offset;
		nskb->ip_summed = skb->ip_summed;

		if (skb->ip_summed == CHECKSUM_PARTIAL)
			start = skb_checksum_start_offset(skb);
		if (start) {
			int offset = start + nskb->csum_offset;

			/* copy the headers, no csum here */
			if (skb_copy_bits(skb, 0, nskb->data, start)) {
				dev_kfree_skb(nskb);
				dev_kfree_skb(skb);
				return NULL;
			}

			/* copy the rest, with csum calculation */
			*(__sum16 *)(skb->data + offset) = 0;
			csum = skb_copy_and_csum_bits(skb, start,
						      nskb->data + start,
						      skb->len - start, 0);

			/* add in the header checksums */
			if (skb->protocol == htons(ETH_P_IP)) {
				struct iphdr *iph = ip_hdr(nskb);

				if (iph->protocol == IPPROTO_TCP ||
				    iph->protocol == IPPROTO_UDP) {
					csum = csum_tcpudp_magic(iph->saddr,
								 iph->daddr,
								 skb->len - start,
								 iph->protocol,
								 csum);
				}
			} else if (skb->protocol == htons(ETH_P_IPV6)) {
				struct ipv6hdr *ip6h = ipv6_hdr(nskb);

				if (ip6h->nexthdr == IPPROTO_TCP ||
				    ip6h->nexthdr == IPPROTO_UDP) {
					csum = csum_ipv6_magic(&ip6h->saddr,
							       &ip6h->daddr,
							       skb->len - start,
							       ip6h->nexthdr,
							       csum);
				}
			}

			/* save the final result */
			*(__sum16 *)(nskb->data + offset) = csum;

			nskb->ip_summed = CHECKSUM_NONE;
		} else if (skb_copy_bits(skb, 0, nskb->data, skb->len)) {
			dev_kfree_skb(nskb);
			dev_kfree_skb(skb);
			return NULL;
		}
		(void)skb_put(nskb, skb->len);
		if (skb_is_gso(skb)) {
			skb_shinfo(nskb)->gso_size = skb_shinfo(skb)->gso_size;
			skb_shinfo(nskb)->gso_type = skb_shinfo(skb)->gso_type;
		}
		nskb->queue_mapping = skb->queue_mapping;
		dev_kfree_skb(skb);
		skb = nskb;
	}
	return skb;
}