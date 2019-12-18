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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int mlx5e_skb_l2_header_offset (struct sk_buff*) ; 
 scalar_t__ skb_transport_header_was_set (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static inline int mlx5e_skb_l3_header_offset(struct sk_buff *skb)
{
	if (skb_transport_header_was_set(skb))
		return skb_transport_offset(skb);
	else
		return mlx5e_skb_l2_header_offset(skb);
}