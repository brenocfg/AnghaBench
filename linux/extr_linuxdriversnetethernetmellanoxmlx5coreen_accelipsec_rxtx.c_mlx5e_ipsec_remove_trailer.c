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
typedef  unsigned int u8 ;
struct xfrm_state {int /*<<< orphan*/  data; } ;
struct sk_buff {unsigned int len; void* protocol; } ;
struct ipv6hdr {void* payload_len; } ;
struct iphdr {void* tot_len; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IP ; 
 unsigned int crypto_aead_authsize (int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ntohs (void*) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,unsigned int) ; 
 int skb_copy_bits (struct sk_buff*,unsigned int,unsigned int*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5e_ipsec_remove_trailer(struct sk_buff *skb, struct xfrm_state *x)
{
	unsigned int alen = crypto_aead_authsize(x->data);
	struct ipv6hdr *ipv6hdr = ipv6_hdr(skb);
	struct iphdr *ipv4hdr = ip_hdr(skb);
	unsigned int trailer_len;
	u8 plen;
	int ret;

	ret = skb_copy_bits(skb, skb->len - alen - 2, &plen, 1);
	if (unlikely(ret))
		return ret;

	trailer_len = alen + plen + 2;

	pskb_trim(skb, skb->len - trailer_len);
	if (skb->protocol == htons(ETH_P_IP)) {
		ipv4hdr->tot_len = htons(ntohs(ipv4hdr->tot_len) - trailer_len);
		ip_send_check(ipv4hdr);
	} else {
		ipv6hdr->payload_len = htons(ntohs(ipv6hdr->payload_len) -
					     trailer_len);
	}
	return 0;
}