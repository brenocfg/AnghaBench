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
struct enetc_tx_swbd {int /*<<< orphan*/ * skb; scalar_t__ dma; } ;
struct enetc_bdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_unmap_tx_buff (struct enetc_bdr*,struct enetc_tx_swbd*) ; 

__attribute__((used)) static void enetc_free_tx_skb(struct enetc_bdr *tx_ring,
			      struct enetc_tx_swbd *tx_swbd)
{
	if (tx_swbd->dma)
		enetc_unmap_tx_buff(tx_ring, tx_swbd);

	if (tx_swbd->skb) {
		dev_kfree_skb_any(tx_swbd->skb);
		tx_swbd->skb = NULL;
	}
}