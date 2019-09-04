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
struct hns3_enet_ring {size_t next_to_clean; size_t next_to_use; TYPE_2__* desc; } ;
struct TYPE_3__ {scalar_t__ bdtp_fe_sc_vld_ra_ri; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_free_buffer_detach (struct hns3_enet_ring*,size_t) ; 
 int /*<<< orphan*/  next_to_clean ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hns3_enet_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_clear_tx_ring(struct hns3_enet_ring *ring)
{
	while (ring->next_to_clean != ring->next_to_use) {
		ring->desc[ring->next_to_clean].tx.bdtp_fe_sc_vld_ra_ri = 0;
		hns3_free_buffer_detach(ring, ring->next_to_clean);
		ring_ptr_move_fw(ring, next_to_clean);
	}
}