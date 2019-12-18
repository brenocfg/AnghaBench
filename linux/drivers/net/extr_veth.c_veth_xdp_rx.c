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
struct veth_rq {int /*<<< orphan*/  xdp_ring; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ptr_ring_produce (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int veth_xdp_rx(struct veth_rq *rq, struct sk_buff *skb)
{
	if (unlikely(ptr_ring_produce(&rq->xdp_ring, skb))) {
		dev_kfree_skb_any(skb);
		return NET_RX_DROP;
	}

	return NET_RX_SUCCESS;
}