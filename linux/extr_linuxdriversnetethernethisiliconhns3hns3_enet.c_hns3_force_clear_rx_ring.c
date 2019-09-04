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
struct hns3_enet_ring {size_t next_to_use; size_t next_to_clean; TYPE_1__* desc_cb; } ;
struct TYPE_2__ {scalar_t__ dma; int /*<<< orphan*/  reuse_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_unmap_buffer (struct hns3_enet_ring*,TYPE_1__*) ; 
 int /*<<< orphan*/  next_to_use ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hns3_enet_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_force_clear_rx_ring(struct hns3_enet_ring *ring)
{
	while (ring->next_to_use != ring->next_to_clean) {
		/* When a buffer is not reused, it's memory has been
		 * freed in hns3_handle_rx_bd or will be freed by
		 * stack, so only need to unmap the buffer here.
		 */
		if (!ring->desc_cb[ring->next_to_use].reuse_flag) {
			hns3_unmap_buffer(ring,
					  &ring->desc_cb[ring->next_to_use]);
			ring->desc_cb[ring->next_to_use].dma = 0;
		}

		ring_ptr_move_fw(ring, next_to_use);
	}
}