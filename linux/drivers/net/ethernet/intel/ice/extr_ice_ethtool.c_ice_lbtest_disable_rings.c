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
struct ice_vsi {int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_NO_RESET ; 
 int /*<<< orphan*/  ice_vsi_free_rx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_tx_rings (struct ice_vsi*) ; 
 int ice_vsi_stop_lan_tx_rings (struct ice_vsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_vsi_stop_rx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ice_lbtest_disable_rings(struct ice_vsi *vsi)
{
	int status;

	status = ice_vsi_stop_lan_tx_rings(vsi, ICE_NO_RESET, 0);
	if (status)
		netdev_err(vsi->netdev, "Failed to stop Tx rings, VSI %d error %d\n",
			   vsi->vsi_num, status);

	status = ice_vsi_stop_rx_rings(vsi);
	if (status)
		netdev_err(vsi->netdev, "Failed to stop Rx rings, VSI %d error %d\n",
			   vsi->vsi_num, status);

	ice_vsi_free_tx_rings(vsi);
	ice_vsi_free_rx_rings(vsi);

	return status;
}