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
struct enetc_tx_swbd {int dummy; } ;
struct enetc_bdr {int bd_count; scalar_t__ next_to_use; scalar_t__ next_to_clean; struct enetc_tx_swbd* tx_swbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_free_tx_skb (struct enetc_bdr*,struct enetc_tx_swbd*) ; 

__attribute__((used)) static void enetc_free_tx_ring(struct enetc_bdr *tx_ring)
{
	int i;

	if (!tx_ring->tx_swbd)
		return;

	for (i = 0; i < tx_ring->bd_count; i++) {
		struct enetc_tx_swbd *tx_swbd = &tx_ring->tx_swbd[i];

		enetc_free_tx_skb(tx_ring, tx_swbd);
	}

	tx_ring->next_to_clean = 0;
	tx_ring->next_to_use = 0;
}