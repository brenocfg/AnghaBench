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
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; void* source; void* dest; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void prepare_udp_hdr(struct sk_buff *skb, __be16 src_port,
			    __be16 dst_port)
{
	struct udphdr *udph;

	__skb_push(skb, sizeof(*udph));
	skb_reset_transport_header(skb);
	udph = udp_hdr(skb);

	udph->dest = dst_port;
	udph->source = src_port;
	udph->len = htons(skb->len);
	udph->check = 0;
}