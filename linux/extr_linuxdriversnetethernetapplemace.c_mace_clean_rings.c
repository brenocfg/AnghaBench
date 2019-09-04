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
struct mace_data {int tx_empty; int tx_fill; int /*<<< orphan*/ ** tx_bufs; int /*<<< orphan*/ ** rx_bufs; } ;

/* Variables and functions */
 int N_RX_RING ; 
 int N_TX_RING ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mace_clean_rings(struct mace_data *mp)
{
    int i;

    /* free some skb's */
    for (i = 0; i < N_RX_RING; ++i) {
	if (mp->rx_bufs[i] != NULL) {
	    dev_kfree_skb(mp->rx_bufs[i]);
	    mp->rx_bufs[i] = NULL;
	}
    }
    for (i = mp->tx_empty; i != mp->tx_fill; ) {
	dev_kfree_skb(mp->tx_bufs[i]);
	if (++i >= N_TX_RING)
	    i = 0;
    }
}