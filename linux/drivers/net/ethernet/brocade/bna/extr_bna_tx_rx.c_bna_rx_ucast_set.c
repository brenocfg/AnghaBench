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
typedef  int /*<<< orphan*/  u8 ;
struct bna_rxf {int ucast_pending_set; int /*<<< orphan*/  cam_fltr_cbarg; int /*<<< orphan*/ * cam_fltr_cbfn; TYPE_3__* ucast_pending_mac; TYPE_1__* rx; } ;
struct bna_rx {TYPE_2__* bna; struct bna_rxf rxf; } ;
typedef  enum bna_cb_status { ____Placeholder_bna_cb_status } bna_cb_status ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  bnad; } ;
struct TYPE_4__ {int /*<<< orphan*/  bna; } ;

/* Variables and functions */
 int BNA_CB_SUCCESS ; 
 int BNA_CB_UCAST_CAM_FULL ; 
 int /*<<< orphan*/  RXF_E_CONFIG ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 TYPE_3__* bna_cam_mod_mac_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_ucam_mod_free_q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

enum bna_cb_status
bna_rx_ucast_set(struct bna_rx *rx, const u8 *ucmac)
{
	struct bna_rxf *rxf = &rx->rxf;

	if (rxf->ucast_pending_mac == NULL) {
		rxf->ucast_pending_mac =
			bna_cam_mod_mac_get(bna_ucam_mod_free_q(rxf->rx->bna));
		if (rxf->ucast_pending_mac == NULL)
			return BNA_CB_UCAST_CAM_FULL;
	}

	ether_addr_copy(rxf->ucast_pending_mac->addr, ucmac);
	rxf->ucast_pending_set = 1;
	rxf->cam_fltr_cbfn = NULL;
	rxf->cam_fltr_cbarg = rx->bna->bnad;

	bfa_fsm_send_event(rxf, RXF_E_CONFIG);

	return BNA_CB_SUCCESS;
}