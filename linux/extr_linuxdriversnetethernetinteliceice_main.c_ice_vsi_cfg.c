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
struct ice_vsi {scalar_t__ netdev; } ;

/* Variables and functions */
 int ice_restore_vlan (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_set_rx_mode (scalar_t__) ; 
 int ice_vsi_cfg_rxqs (struct ice_vsi*) ; 
 int ice_vsi_cfg_txqs (struct ice_vsi*) ; 

__attribute__((used)) static int ice_vsi_cfg(struct ice_vsi *vsi)
{
	int err;

	if (vsi->netdev) {
		ice_set_rx_mode(vsi->netdev);
		err = ice_restore_vlan(vsi);
		if (err)
			return err;
	}

	err = ice_vsi_cfg_txqs(vsi);
	if (!err)
		err = ice_vsi_cfg_rxqs(vsi);

	return err;
}