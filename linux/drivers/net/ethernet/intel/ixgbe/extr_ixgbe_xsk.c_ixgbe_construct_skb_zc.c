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
struct xdp_buff {unsigned int data; unsigned int data_meta; unsigned int data_end; unsigned int data_hard_start; } ;
struct sk_buff {int dummy; } ;
struct ixgbe_rx_buffer {int dummy; } ;
struct ixgbe_ring {TYPE_1__* q_vector; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int __GFP_NOWARN ; 
 struct sk_buff* __napi_alloc_skb (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ixgbe_reuse_rx_buffer_zc (struct ixgbe_ring*,struct ixgbe_rx_buffer*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skb_metadata_set (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *ixgbe_construct_skb_zc(struct ixgbe_ring *rx_ring,
					      struct ixgbe_rx_buffer *bi,
					      struct xdp_buff *xdp)
{
	unsigned int metasize = xdp->data - xdp->data_meta;
	unsigned int datasize = xdp->data_end - xdp->data;
	struct sk_buff *skb;

	/* allocate a skb to store the frags */
	skb = __napi_alloc_skb(&rx_ring->q_vector->napi,
			       xdp->data_end - xdp->data_hard_start,
			       GFP_ATOMIC | __GFP_NOWARN);
	if (unlikely(!skb))
		return NULL;

	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	memcpy(__skb_put(skb, datasize), xdp->data, datasize);
	if (metasize)
		skb_metadata_set(skb, metasize);

	ixgbe_reuse_rx_buffer_zc(rx_ring, bi);
	return skb;
}