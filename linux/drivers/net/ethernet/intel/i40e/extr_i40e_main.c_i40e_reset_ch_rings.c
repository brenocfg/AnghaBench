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
typedef  size_t u16 ;
struct i40e_vsi {struct i40e_ring** rx_rings; struct i40e_ring** tx_rings; } ;
struct i40e_ring {int /*<<< orphan*/ * ch; } ;
struct i40e_channel {int num_queue_pairs; size_t base_queue; } ;

/* Variables and functions */

__attribute__((used)) static void i40e_reset_ch_rings(struct i40e_vsi *vsi, struct i40e_channel *ch)
{
	struct i40e_ring *tx_ring, *rx_ring;
	u16 pf_q;
	int i;

	for (i = 0; i < ch->num_queue_pairs; i++) {
		pf_q = ch->base_queue + i;
		tx_ring = vsi->tx_rings[pf_q];
		tx_ring->ch = NULL;
		rx_ring = vsi->rx_rings[pf_q];
		rx_ring->ch = NULL;
	}
}