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
struct ice_vsi {scalar_t__ type; int /*<<< orphan*/ * netdev; int /*<<< orphan*/  state; int /*<<< orphan*/  idx; int /*<<< orphan*/  port_info; scalar_t__ num_q_vectors; int /*<<< orphan*/  base_vector; struct ice_pf* back; } ;
struct ice_pf {int /*<<< orphan*/  state; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; int /*<<< orphan*/  num_avail_sw_msix; int /*<<< orphan*/  irq_tracker; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ICE_FLAG_FW_LLDP_AGENT ; 
 int /*<<< orphan*/  ICE_FLAG_RSS_ENA ; 
 scalar_t__ ICE_VSI_LB ; 
 scalar_t__ ICE_VSI_PF ; 
 scalar_t__ ICE_VSI_VF ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_cfg_sw_lldp (struct ice_vsi*,int,int) ; 
 int /*<<< orphan*/  ice_free_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_is_reset_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_is_safe_mode (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_remove_vsi_fltr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_rm_vsi_lan_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_rss_clean (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_add_rem_eth_mac (struct ice_vsi*,int) ; 
 int /*<<< orphan*/  ice_vsi_clear (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_clear_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_close (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_delete (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_dis_irq (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_q_vectors (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_put_qs (struct ice_vsi*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 

int ice_vsi_release(struct ice_vsi *vsi)
{
	struct ice_pf *pf;

	if (!vsi->back)
		return -ENODEV;
	pf = vsi->back;

	/* do not unregister while driver is in the reset recovery pending
	 * state. Since reset/rebuild happens through PF service task workqueue,
	 * it's not a good idea to unregister netdev that is associated to the
	 * PF that is running the work queue items currently. This is done to
	 * avoid check_flush_dependency() warning on this wq
	 */
	if (vsi->netdev && !ice_is_reset_in_progress(pf->state))
		unregister_netdev(vsi->netdev);

	if (test_bit(ICE_FLAG_RSS_ENA, pf->flags))
		ice_rss_clean(vsi);

	/* Disable VSI and free resources */
	if (vsi->type != ICE_VSI_LB)
		ice_vsi_dis_irq(vsi);
	ice_vsi_close(vsi);

	/* SR-IOV determines needed MSIX resources all at once instead of per
	 * VSI since when VFs are spawned we know how many VFs there are and how
	 * many interrupts each VF needs. SR-IOV MSIX resources are also
	 * cleared in the same manner.
	 */
	if (vsi->type != ICE_VSI_VF) {
		/* reclaim SW interrupts back to the common pool */
		ice_free_res(pf->irq_tracker, vsi->base_vector, vsi->idx);
		pf->num_avail_sw_msix += vsi->num_q_vectors;
	}

	if (!ice_is_safe_mode(pf)) {
		if (vsi->type == ICE_VSI_PF) {
			ice_vsi_add_rem_eth_mac(vsi, false);
			ice_cfg_sw_lldp(vsi, true, false);
			/* The Rx rule will only exist to remove if the LLDP FW
			 * engine is currently stopped
			 */
			if (!test_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags))
				ice_cfg_sw_lldp(vsi, false, false);
		}
	}

	ice_remove_vsi_fltr(&pf->hw, vsi->idx);
	ice_rm_vsi_lan_cfg(vsi->port_info, vsi->idx);
	ice_vsi_delete(vsi);
	ice_vsi_free_q_vectors(vsi);

	/* make sure unregister_netdev() was called by checking __ICE_DOWN */
	if (vsi->netdev && test_bit(__ICE_DOWN, vsi->state)) {
		free_netdev(vsi->netdev);
		vsi->netdev = NULL;
	}

	ice_vsi_clear_rings(vsi);

	ice_vsi_put_qs(vsi);

	/* retain SW VSI data structure since it is needed to unregister and
	 * free VSI netdev when PF is not in reset recovery pending state,\
	 * for ex: during rmmod.
	 */
	if (!ice_is_reset_in_progress(pf->state))
		ice_vsi_clear(vsi);

	return 0;
}