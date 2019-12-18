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
struct ice_vsi {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  ice_down (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_irq (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_rx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_tx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ice_vsi_close(struct ice_vsi *vsi)
{
	if (!test_and_set_bit(__ICE_DOWN, vsi->state))
		ice_down(vsi);

	ice_vsi_free_irq(vsi);
	ice_vsi_free_tx_rings(vsi);
	ice_vsi_free_rx_rings(vsi);
}