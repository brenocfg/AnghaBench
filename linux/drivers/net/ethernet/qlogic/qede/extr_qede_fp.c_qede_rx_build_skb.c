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
struct sw_rx_data {int /*<<< orphan*/  data; int /*<<< orphan*/  page_offset; } ;
struct sk_buff {int dummy; } ;
struct qede_rx_queue {int dummy; } ;
struct qede_dev {scalar_t__ rx_copybreak; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDE_RX_HDR_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_ref_inc (int /*<<< orphan*/ ) ; 
 struct sk_buff* qede_build_skb (struct qede_rx_queue*,struct sw_rx_data*,scalar_t__,scalar_t__) ; 
 int qede_realloc_rx_buffer (struct qede_rx_queue*,struct sw_rx_data*) ; 
 int /*<<< orphan*/  qede_reuse_page (struct qede_rx_queue*,struct sw_rx_data*) ; 
 int /*<<< orphan*/  qede_rx_bd_ring_consume (struct qede_rx_queue*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *
qede_rx_build_skb(struct qede_dev *edev,
		  struct qede_rx_queue *rxq,
		  struct sw_rx_data *bd, u16 len, u16 pad)
{
	struct sk_buff *skb = NULL;

	/* For smaller frames still need to allocate skb, memcpy
	 * data and benefit in reusing the page segment instead of
	 * un-mapping it.
	 */
	if ((len + pad <= edev->rx_copybreak)) {
		unsigned int offset = bd->page_offset + pad;

		skb = netdev_alloc_skb(edev->ndev, QEDE_RX_HDR_SIZE);
		if (unlikely(!skb))
			return NULL;

		skb_reserve(skb, pad);
		skb_put_data(skb, page_address(bd->data) + offset, len);
		qede_reuse_page(rxq, bd);
		goto out;
	}

	skb = qede_build_skb(rxq, bd, len, pad);

	if (unlikely(qede_realloc_rx_buffer(rxq, bd))) {
		/* Incr page ref count to reuse on allocation failure so
		 * that it doesn't get freed while freeing SKB [as its
		 * already mapped there].
		 */
		page_ref_inc(bd->data);
		dev_kfree_skb_any(skb);
		return NULL;
	}
out:
	/* We've consumed the first BD and prepared an SKB */
	qede_rx_bd_ring_consume(rxq);

	return skb;
}