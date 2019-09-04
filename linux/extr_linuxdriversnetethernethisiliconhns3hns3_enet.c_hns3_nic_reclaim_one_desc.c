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
struct hns3_enet_ring {size_t next_to_clean; struct hns3_desc_cb* desc_cb; } ;
struct hns3_desc_cb {scalar_t__ type; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ DESC_TYPE_SKB ; 
 int /*<<< orphan*/  hns3_free_buffer_detach (struct hns3_enet_ring*,size_t) ; 
 int /*<<< orphan*/  next_to_clean ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hns3_enet_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_nic_reclaim_one_desc(struct hns3_enet_ring *ring, int *bytes,
				      int *pkts)
{
	struct hns3_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_clean];

	(*pkts) += (desc_cb->type == DESC_TYPE_SKB);
	(*bytes) += desc_cb->length;
	/* desc_cb will be cleaned, after hnae3_free_buffer_detach*/
	hns3_free_buffer_detach(ring, ring->next_to_clean);

	ring_ptr_move_fw(ring, next_to_clean);
}