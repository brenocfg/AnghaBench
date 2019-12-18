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
struct bnxt_rx_ring_info {TYPE_1__* rx_tpa; TYPE_1__* rx_tpa_idx_map; } ;
struct bnxt {int rx_nr_rings; struct bnxt_rx_ring_info* rx_ring; } ;
struct TYPE_2__ {struct TYPE_2__* agg_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void bnxt_free_tpa_info(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->rx_nr_rings; i++) {
		struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];

		kfree(rxr->rx_tpa_idx_map);
		rxr->rx_tpa_idx_map = NULL;
		if (rxr->rx_tpa) {
			kfree(rxr->rx_tpa[0].agg_arr);
			rxr->rx_tpa[0].agg_arr = NULL;
		}
		kfree(rxr->rx_tpa);
		rxr->rx_tpa = NULL;
	}
}