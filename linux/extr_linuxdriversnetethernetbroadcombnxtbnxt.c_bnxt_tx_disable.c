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
struct bnxt_tx_ring_info {int /*<<< orphan*/  dev_state; } ;
struct bnxt {int tx_nr_rings; int /*<<< orphan*/  dev; struct bnxt_tx_ring_info* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_DEV_STATE_CLOSING ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 

void bnxt_tx_disable(struct bnxt *bp)
{
	int i;
	struct bnxt_tx_ring_info *txr;

	if (bp->tx_ring) {
		for (i = 0; i < bp->tx_nr_rings; i++) {
			txr = &bp->tx_ring[i];
			txr->dev_state = BNXT_DEV_STATE_CLOSING;
		}
	}
	/* Stop all TX queues */
	netif_tx_disable(bp->dev);
	netif_carrier_off(bp->dev);
}