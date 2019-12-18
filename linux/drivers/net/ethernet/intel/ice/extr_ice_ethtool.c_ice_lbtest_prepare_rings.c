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
struct ice_vsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_NO_RESET ; 
 int ice_vsi_cfg (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_rx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_tx_rings (struct ice_vsi*) ; 
 int ice_vsi_setup_rx_rings (struct ice_vsi*) ; 
 int ice_vsi_setup_tx_rings (struct ice_vsi*) ; 
 int ice_vsi_start_rx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_stop_lan_tx_rings (struct ice_vsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_lbtest_prepare_rings(struct ice_vsi *vsi)
{
	int status;

	status = ice_vsi_setup_tx_rings(vsi);
	if (status)
		goto err_setup_tx_ring;

	status = ice_vsi_setup_rx_rings(vsi);
	if (status)
		goto err_setup_rx_ring;

	status = ice_vsi_cfg(vsi);
	if (status)
		goto err_setup_rx_ring;

	status = ice_vsi_start_rx_rings(vsi);
	if (status)
		goto err_start_rx_ring;

	return status;

err_start_rx_ring:
	ice_vsi_free_rx_rings(vsi);
err_setup_rx_ring:
	ice_vsi_stop_lan_tx_rings(vsi, ICE_NO_RESET, 0);
err_setup_tx_ring:
	ice_vsi_free_tx_rings(vsi);

	return status;
}