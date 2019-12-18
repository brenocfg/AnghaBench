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
struct i40e_vsi {scalar_t__ type; int num_queue_pairs; int /*<<< orphan*/ * rx_rings; int /*<<< orphan*/ * xdp_rings; int /*<<< orphan*/ * tx_rings; TYPE_1__* back; scalar_t__ netdev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED ; 
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  i40e_clean_rx_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_clean_tx_ring (int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_force_link_state (TYPE_1__*,int) ; 
 int /*<<< orphan*/  i40e_napi_disable_all (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_disable_irq (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_stop_rings (struct i40e_vsi*) ; 
 int /*<<< orphan*/  netif_carrier_off (scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_disable (scalar_t__) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void i40e_down(struct i40e_vsi *vsi)
{
	int i;

	/* It is assumed that the caller of this function
	 * sets the vsi->state __I40E_VSI_DOWN bit.
	 */
	if (vsi->netdev) {
		netif_carrier_off(vsi->netdev);
		netif_tx_disable(vsi->netdev);
	}
	i40e_vsi_disable_irq(vsi);
	i40e_vsi_stop_rings(vsi);
	if (vsi->type == I40E_VSI_MAIN &&
	    vsi->back->flags & I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED)
		i40e_force_link_state(vsi->back, false);
	i40e_napi_disable_all(vsi);

	for (i = 0; i < vsi->num_queue_pairs; i++) {
		i40e_clean_tx_ring(vsi->tx_rings[i]);
		if (i40e_enabled_xdp_vsi(vsi)) {
			/* Make sure that in-progress ndo_xdp_xmit
			 * calls are completed.
			 */
			synchronize_rcu();
			i40e_clean_tx_ring(vsi->xdp_rings[i]);
		}
		i40e_clean_rx_ring(vsi->rx_rings[i]);
	}

}