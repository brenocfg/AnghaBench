#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ice_vsi {scalar_t__ alloc_rxq; scalar_t__ alloc_txq; TYPE_4__* netdev; TYPE_2__* port_info; } ;
struct TYPE_11__ {int /*<<< orphan*/  port_info; } ;
struct ice_pf {int /*<<< orphan*/  q_left_rx; int /*<<< orphan*/  q_left_tx; TYPE_3__* pdev; TYPE_5__ hw; struct ice_vsi** vsi; int /*<<< orphan*/  state; } ;
struct TYPE_10__ {scalar_t__ reg_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * perm_addr; } ;
struct TYPE_8__ {TYPE_1__ mac; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ICE_VSI_PF ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (TYPE_4__*) ; 
 int ice_add_mac (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int ice_add_mac_to_list (struct ice_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_is_reset_recovery_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_vsi_clear (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_delete (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_q_vectors (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_put_qs (struct ice_vsi*) ; 
 int ice_vsi_reinit_setup (struct ice_vsi*) ; 
 struct ice_vsi* ice_vsi_setup (struct ice_pf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmp_add_list ; 
 int /*<<< orphan*/  unregister_netdev (TYPE_4__*) ; 

__attribute__((used)) static int ice_setup_pf_sw(struct ice_pf *pf)
{
	LIST_HEAD(tmp_add_list);
	u8 broadcast[ETH_ALEN];
	struct ice_vsi *vsi;
	int status = 0;

	if (!ice_is_reset_recovery_pending(pf->state)) {
		vsi = ice_vsi_setup(pf, ICE_VSI_PF, pf->hw.port_info);
		if (!vsi) {
			status = -ENOMEM;
			goto error_exit;
		}
	} else {
		vsi = pf->vsi[0];
		status = ice_vsi_reinit_setup(vsi);
		if (status < 0)
			return -EIO;
	}

	/* tmp_add_list contains a list of MAC addresses for which MAC
	 * filters need to be programmed. Add the VSI's unicast MAC to
	 * this list
	 */
	status = ice_add_mac_to_list(vsi, &tmp_add_list,
				     vsi->port_info->mac.perm_addr);
	if (status)
		goto error_exit;

	/* VSI needs to receive broadcast traffic, so add the broadcast
	 * MAC address to the list.
	 */
	eth_broadcast_addr(broadcast);
	status = ice_add_mac_to_list(vsi, &tmp_add_list, broadcast);
	if (status)
		goto error_exit;

	/* program MAC filters for entries in tmp_add_list */
	status = ice_add_mac(&pf->hw, &tmp_add_list);
	if (status) {
		dev_err(&pf->pdev->dev, "Could not add MAC filters\n");
		status = -ENOMEM;
		goto error_exit;
	}

	ice_free_fltr_list(&pf->pdev->dev, &tmp_add_list);
	return status;

error_exit:
	ice_free_fltr_list(&pf->pdev->dev, &tmp_add_list);

	if (vsi) {
		ice_vsi_free_q_vectors(vsi);
		if (vsi->netdev && vsi->netdev->reg_state == NETREG_REGISTERED)
			unregister_netdev(vsi->netdev);
		if (vsi->netdev) {
			free_netdev(vsi->netdev);
			vsi->netdev = NULL;
		}

		ice_vsi_delete(vsi);
		ice_vsi_put_qs(vsi);
		pf->q_left_tx += vsi->alloc_txq;
		pf->q_left_rx += vsi->alloc_rxq;
		ice_vsi_clear(vsi);
	}
	return status;
}