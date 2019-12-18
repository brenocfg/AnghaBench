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
struct ice_vsi {int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
struct ice_vf {int port_vlan_id; int num_mac; TYPE_1__ dflt_lan_addr; int /*<<< orphan*/  lan_vsi_num; int /*<<< orphan*/  lan_vsi_idx; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  first_vector_idx; struct ice_pf* pf; } ;
struct TYPE_6__ {int /*<<< orphan*/  port_info; } ;
struct ice_pf {TYPE_2__* pdev; TYPE_3__ hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int ICE_VLAN_M ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ *) ; 
 int ice_add_mac (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ice_add_mac_to_list (struct ice_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_calc_vf_first_vector_idx (struct ice_pf*,struct ice_vf*) ; 
 int /*<<< orphan*/  ice_free_fltr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ice_vsi* ice_vf_vsi_setup (struct ice_pf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_vsi_add_vlan (struct ice_vsi*,int) ; 
 int /*<<< orphan*/  ice_vsi_manage_pvid (struct ice_vsi*,int,int) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_add_list ; 

__attribute__((used)) static int ice_alloc_vsi_res(struct ice_vf *vf)
{
	struct ice_pf *pf = vf->pf;
	LIST_HEAD(tmp_add_list);
	u8 broadcast[ETH_ALEN];
	struct ice_vsi *vsi;
	int status = 0;

	/* first vector index is the VFs OICR index */
	vf->first_vector_idx = ice_calc_vf_first_vector_idx(pf, vf);

	vsi = ice_vf_vsi_setup(pf, pf->hw.port_info, vf->vf_id);
	if (!vsi) {
		dev_err(&pf->pdev->dev, "Failed to create VF VSI\n");
		return -ENOMEM;
	}

	vf->lan_vsi_idx = vsi->idx;
	vf->lan_vsi_num = vsi->vsi_num;

	/* Check if port VLAN exist before, and restore it accordingly */
	if (vf->port_vlan_id) {
		ice_vsi_manage_pvid(vsi, vf->port_vlan_id, true);
		ice_vsi_add_vlan(vsi, vf->port_vlan_id & ICE_VLAN_M);
	}

	eth_broadcast_addr(broadcast);

	status = ice_add_mac_to_list(vsi, &tmp_add_list, broadcast);
	if (status)
		goto ice_alloc_vsi_res_exit;

	if (is_valid_ether_addr(vf->dflt_lan_addr.addr)) {
		status = ice_add_mac_to_list(vsi, &tmp_add_list,
					     vf->dflt_lan_addr.addr);
		if (status)
			goto ice_alloc_vsi_res_exit;
	}

	status = ice_add_mac(&pf->hw, &tmp_add_list);
	if (status)
		dev_err(&pf->pdev->dev,
			"could not add mac filters error %d\n", status);
	else
		vf->num_mac = 1;

	/* Clear this bit after VF initialization since we shouldn't reclaim
	 * and reassign interrupts for synchronous or asynchronous VFR events.
	 * We don't want to reconfigure interrupts since AVF driver doesn't
	 * expect vector assignment to be changed unless there is a request for
	 * more vectors.
	 */
ice_alloc_vsi_res_exit:
	ice_free_fltr_list(&pf->pdev->dev, &tmp_add_list);
	return status;
}