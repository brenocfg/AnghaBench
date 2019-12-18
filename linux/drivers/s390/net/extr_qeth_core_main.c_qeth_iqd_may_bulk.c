#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct qeth_qdio_out_q {struct qeth_hdr* prev_hdr; } ;
struct qeth_qdio_out_buffer {int /*<<< orphan*/  skb_list; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {int /*<<< orphan*/  l3; TYPE_2__ l2; } ;
struct qeth_hdr {TYPE_1__ hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 scalar_t__ QETH_HEADER_TYPE_LAYER2 ; 
 TYPE_4__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_l2_same_vlan (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ qeth_l3_iqd_same_vlan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_l3_same_next_hop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool qeth_iqd_may_bulk(struct qeth_qdio_out_q *queue,
			      struct qeth_qdio_out_buffer *buffer,
			      struct sk_buff *curr_skb,
			      struct qeth_hdr *curr_hdr)
{
	struct qeth_hdr *prev_hdr = queue->prev_hdr;

	if (!prev_hdr)
		return true;

	/* All packets must have the same target: */
	if (curr_hdr->hdr.l2.id == QETH_HEADER_TYPE_LAYER2) {
		struct sk_buff *prev_skb = skb_peek(&buffer->skb_list);

		return ether_addr_equal(eth_hdr(prev_skb)->h_dest,
					eth_hdr(curr_skb)->h_dest) &&
		       qeth_l2_same_vlan(&prev_hdr->hdr.l2, &curr_hdr->hdr.l2);
	}

	return qeth_l3_same_next_hop(&prev_hdr->hdr.l3, &curr_hdr->hdr.l3) &&
	       qeth_l3_iqd_same_vlan(&prev_hdr->hdr.l3, &curr_hdr->hdr.l3);
}