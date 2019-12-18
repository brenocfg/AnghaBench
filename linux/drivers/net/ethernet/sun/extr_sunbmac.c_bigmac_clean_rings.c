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
struct bigmac {int /*<<< orphan*/ ** tx_skbs; int /*<<< orphan*/ ** rx_skbs; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bigmac_clean_rings(struct bigmac *bp)
{
	int i;

	for (i = 0; i < RX_RING_SIZE; i++) {
		if (bp->rx_skbs[i] != NULL) {
			dev_kfree_skb_any(bp->rx_skbs[i]);
			bp->rx_skbs[i] = NULL;
		}
	}

	for (i = 0; i < TX_RING_SIZE; i++) {
		if (bp->tx_skbs[i] != NULL) {
			dev_kfree_skb_any(bp->tx_skbs[i]);
			bp->tx_skbs[i] = NULL;
		}
	}
}