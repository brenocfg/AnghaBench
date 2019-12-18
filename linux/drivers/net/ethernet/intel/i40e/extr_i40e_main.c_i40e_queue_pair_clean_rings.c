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
struct i40e_vsi {int /*<<< orphan*/ * rx_rings; int /*<<< orphan*/ * xdp_rings; int /*<<< orphan*/ * tx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_clean_rx_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_clean_tx_ring (int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void i40e_queue_pair_clean_rings(struct i40e_vsi *vsi, int queue_pair)
{
	i40e_clean_tx_ring(vsi->tx_rings[queue_pair]);
	if (i40e_enabled_xdp_vsi(vsi)) {
		/* Make sure that in-progress ndo_xdp_xmit calls are
		 * completed.
		 */
		synchronize_rcu();
		i40e_clean_tx_ring(vsi->xdp_rings[queue_pair]);
	}
	i40e_clean_rx_ring(vsi->rx_rings[queue_pair]);
}