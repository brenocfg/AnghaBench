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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; } ;
struct ixgbe_ring {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  append_cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  gso_type; int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* IXGBE_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  SKB_GSO_TCPV4 ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void ixgbe_set_rsc_gso_size(struct ixgbe_ring *ring,
				   struct sk_buff *skb)
{
	u16 hdr_len = skb_headlen(skb);

	/* set gso_size to avoid messing up TCP MSS */
	skb_shinfo(skb)->gso_size = DIV_ROUND_UP((skb->len - hdr_len),
						 IXGBE_CB(skb)->append_cnt);
	skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
}