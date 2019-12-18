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
struct sk_buff {int /*<<< orphan*/  encapsulation; } ;

/* Variables and functions */
 unsigned int inner_tcp_hdrlen (struct sk_buff*) ; 
 unsigned int skb_inner_transport_offset (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static unsigned int hns3_gso_hdr_len(struct sk_buff *skb)
{
	if (!skb->encapsulation)
		return skb_transport_offset(skb) + tcp_hdrlen(skb);

	return skb_inner_transport_offset(skb) + inner_tcp_hdrlen(skb);
}