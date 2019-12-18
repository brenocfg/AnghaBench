#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {scalar_t__ netdev; TYPE_3__* port_info; int /*<<< orphan*/  state; struct ice_pf* back; } ;
struct ice_pf {int dummy; } ;
struct TYPE_4__ {int link_info; } ;
struct TYPE_5__ {TYPE_1__ link_info; } ;
struct TYPE_6__ {TYPE_2__ phy; } ;

/* Variables and functions */
 int ICE_AQ_LINK_UP ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_napi_enable_all (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_print_link_msg (struct ice_vsi*,int) ; 
 int /*<<< orphan*/  ice_service_task_schedule (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_vsi_cfg_msix (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_ena_irq (struct ice_vsi*) ; 
 int ice_vsi_start_rx_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  netif_carrier_on (scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (scalar_t__) ; 

__attribute__((used)) static int ice_up_complete(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	int err;

	ice_vsi_cfg_msix(vsi);

	/* Enable only Rx rings, Tx rings were enabled by the FW when the
	 * Tx queue group list was configured and the context bits were
	 * programmed using ice_vsi_cfg_txqs
	 */
	err = ice_vsi_start_rx_rings(vsi);
	if (err)
		return err;

	clear_bit(__ICE_DOWN, vsi->state);
	ice_napi_enable_all(vsi);
	ice_vsi_ena_irq(vsi);

	if (vsi->port_info &&
	    (vsi->port_info->phy.link_info.link_info & ICE_AQ_LINK_UP) &&
	    vsi->netdev) {
		ice_print_link_msg(vsi, true);
		netif_tx_start_all_queues(vsi->netdev);
		netif_carrier_on(vsi->netdev);
	}

	ice_service_task_schedule(pf);

	return 0;
}