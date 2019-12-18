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
 int i40e_configure_rx_ring (int /*<<< orphan*/ ) ; 
 int i40e_configure_tx_ring (int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_exit_busy_conf (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_queue_pair_enable_irq (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_queue_pair_toggle_napi (struct i40e_vsi*,int,int) ; 
 int i40e_queue_pair_toggle_rings (struct i40e_vsi*,int,int) ; 

int i40e_queue_pair_enable(struct i40e_vsi *vsi, int queue_pair)
{
	int err;

	err = i40e_configure_tx_ring(vsi->tx_rings[queue_pair]);
	if (err)
		return err;

	if (i40e_enabled_xdp_vsi(vsi)) {
		err = i40e_configure_tx_ring(vsi->xdp_rings[queue_pair]);
		if (err)
			return err;
	}

	err = i40e_configure_rx_ring(vsi->rx_rings[queue_pair]);
	if (err)
		return err;

	err = i40e_queue_pair_toggle_rings(vsi, queue_pair, true /* on */);
	i40e_queue_pair_toggle_napi(vsi, queue_pair, true /* on */);
	i40e_queue_pair_enable_irq(vsi, queue_pair);

	i40e_exit_busy_conf(vsi);

	return err;
}