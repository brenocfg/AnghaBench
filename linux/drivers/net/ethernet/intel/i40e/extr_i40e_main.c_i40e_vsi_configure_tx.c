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
struct i40e_vsi {size_t num_queue_pairs; int /*<<< orphan*/ * xdp_rings; int /*<<< orphan*/ * tx_rings; } ;

/* Variables and functions */
 int i40e_configure_tx_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 

__attribute__((used)) static int i40e_vsi_configure_tx(struct i40e_vsi *vsi)
{
	int err = 0;
	u16 i;

	for (i = 0; (i < vsi->num_queue_pairs) && !err; i++)
		err = i40e_configure_tx_ring(vsi->tx_rings[i]);

	if (err || !i40e_enabled_xdp_vsi(vsi))
		return err;

	for (i = 0; (i < vsi->num_queue_pairs) && !err; i++)
		err = i40e_configure_tx_ring(vsi->xdp_rings[i]);

	return err;
}