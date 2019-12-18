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
struct pasemi_mac_txring {int next_to_clean; int next_to_fill; int /*<<< orphan*/  chan; struct pasemi_mac_buffer* ring_info; } ;
struct pasemi_mac_buffer {scalar_t__ skb; scalar_t__ dma; } ;
struct pasemi_mac {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SKB_FRAGS ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  kfree (struct pasemi_mac_buffer*) ; 
 int /*<<< orphan*/  pasemi_dma_free_chan (int /*<<< orphan*/ *) ; 
 int pasemi_mac_unmap_tx_skb (struct pasemi_mac*,int,scalar_t__,scalar_t__*) ; 
 TYPE_1__* skb_shinfo (scalar_t__) ; 
 struct pasemi_mac_txring* tx_ring (struct pasemi_mac*) ; 

__attribute__((used)) static void pasemi_mac_free_tx_resources(struct pasemi_mac *mac)
{
	struct pasemi_mac_txring *txring = tx_ring(mac);
	unsigned int i, j;
	struct pasemi_mac_buffer *info;
	dma_addr_t dmas[MAX_SKB_FRAGS+1];
	int freed, nfrags;
	int start, limit;

	start = txring->next_to_clean;
	limit = txring->next_to_fill;

	/* Compensate for when fill has wrapped and clean has not */
	if (start > limit)
		limit += TX_RING_SIZE;

	for (i = start; i < limit; i += freed) {
		info = &txring->ring_info[(i+1) & (TX_RING_SIZE-1)];
		if (info->dma && info->skb) {
			nfrags = skb_shinfo(info->skb)->nr_frags;
			for (j = 0; j <= nfrags; j++)
				dmas[j] = txring->ring_info[(i+1+j) &
						(TX_RING_SIZE-1)].dma;
			freed = pasemi_mac_unmap_tx_skb(mac, nfrags,
							info->skb, dmas);
		} else {
			freed = 2;
		}
	}

	kfree(txring->ring_info);
	pasemi_dma_free_chan(&txring->chan);

}