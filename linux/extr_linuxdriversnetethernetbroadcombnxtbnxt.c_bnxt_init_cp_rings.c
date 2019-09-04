#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bnxt_ring_struct {int /*<<< orphan*/  fw_ring_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  coal_bufs; int /*<<< orphan*/  coal_ticks; } ;
struct bnxt_cp_ring_info {TYPE_1__ rx_ring_coal; struct bnxt_ring_struct cp_ring_struct; } ;
struct TYPE_5__ {int /*<<< orphan*/  coal_bufs; int /*<<< orphan*/  coal_ticks; } ;
struct bnxt {int cp_nr_rings; TYPE_2__ rx_coal; TYPE_3__** bnapi; } ;
struct TYPE_6__ {struct bnxt_cp_ring_info cp_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_HW_RING_ID ; 

__attribute__((used)) static void bnxt_init_cp_rings(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_cp_ring_info *cpr = &bp->bnapi[i]->cp_ring;
		struct bnxt_ring_struct *ring = &cpr->cp_ring_struct;

		ring->fw_ring_id = INVALID_HW_RING_ID;
		cpr->rx_ring_coal.coal_ticks = bp->rx_coal.coal_ticks;
		cpr->rx_ring_coal.coal_bufs = bp->rx_coal.coal_bufs;
	}
}