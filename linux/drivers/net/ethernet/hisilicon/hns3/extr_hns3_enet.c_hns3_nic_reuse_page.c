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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct hns3_enet_ring {size_t next_to_clean; struct hns3_desc* desc; } ;
struct hns3_desc_cb {scalar_t__ page_offset; int reuse_flag; int /*<<< orphan*/  priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct hns3_desc {TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 scalar_t__ hns3_buf_size (struct hns3_enet_ring*) ; 
 scalar_t__ hns3_page_size (struct hns3_enet_ring*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ numa_mem_id () ; 
 int page_count (int /*<<< orphan*/ ) ; 
 scalar_t__ page_to_nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hns3_nic_reuse_page(struct sk_buff *skb, int i,
				struct hns3_enet_ring *ring, int pull_len,
				struct hns3_desc_cb *desc_cb)
{
	struct hns3_desc *desc = &ring->desc[ring->next_to_clean];
	int size = le16_to_cpu(desc->rx.size);
	u32 truesize = hns3_buf_size(ring);

	skb_add_rx_frag(skb, i, desc_cb->priv, desc_cb->page_offset + pull_len,
			size - pull_len, truesize);

	/* Avoid re-using remote pages, or the stack is still using the page
	 * when page_offset rollback to zero, flag default unreuse
	 */
	if (unlikely(page_to_nid(desc_cb->priv) != numa_mem_id()) ||
	    (!desc_cb->page_offset && page_count(desc_cb->priv) > 1))
		return;

	/* Move offset up to the next cache line */
	desc_cb->page_offset += truesize;

	if (desc_cb->page_offset + truesize <= hns3_page_size(ring)) {
		desc_cb->reuse_flag = 1;
		/* Bump ref count on page before it is given */
		get_page(desc_cb->priv);
	} else if (page_count(desc_cb->priv) == 1) {
		desc_cb->reuse_flag = 1;
		desc_cb->page_offset = 0;
		get_page(desc_cb->priv);
	}
}