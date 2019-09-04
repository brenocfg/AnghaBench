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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ inner_tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ skb_inner_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static u16 qede_get_skb_hlen(struct sk_buff *skb, bool is_encap_pkt)
{
	if (is_encap_pkt)
		return (skb_inner_transport_header(skb) +
			inner_tcp_hdrlen(skb) - skb->data);
	else
		return (skb_transport_header(skb) +
			tcp_hdrlen(skb) - skb->data);
}