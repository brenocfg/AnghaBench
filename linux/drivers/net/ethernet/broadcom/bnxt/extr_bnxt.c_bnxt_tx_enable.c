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
struct bnxt_tx_ring_info {scalar_t__ dev_state; } ;
struct TYPE_2__ {scalar_t__ link_up; } ;
struct bnxt {int tx_nr_rings; int /*<<< orphan*/  dev; TYPE_1__ link_info; struct bnxt_tx_ring_info* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 

void bnxt_tx_enable(struct bnxt *bp)
{
	int i;
	struct bnxt_tx_ring_info *txr;

	for (i = 0; i < bp->tx_nr_rings; i++) {
		txr = &bp->tx_ring[i];
		txr->dev_state = 0;
	}
	netif_tx_wake_all_queues(bp->dev);
	if (bp->link_info.link_up)
		netif_carrier_on(bp->dev);
}