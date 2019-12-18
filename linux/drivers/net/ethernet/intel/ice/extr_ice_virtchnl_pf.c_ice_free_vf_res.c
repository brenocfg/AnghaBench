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
struct ice_vf {int lan_vsi_idx; int first_vector_idx; int /*<<< orphan*/  vf_states; scalar_t__ num_mac; scalar_t__ lan_vsi_num; struct ice_pf* pf; } ;
struct ice_pf {int num_vf_msix; int /*<<< orphan*/  hw; int /*<<< orphan*/ * vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_DYN_CTL (int) ; 
 int /*<<< orphan*/  GLINT_DYN_CTL_CLEARPBA_M ; 
 int /*<<< orphan*/  ICE_VF_STATE_INIT ; 
 int /*<<< orphan*/  ICE_VF_STATE_MC_PROMISC ; 
 int /*<<< orphan*/  ICE_VF_STATE_UC_PROMISC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_vsi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_free_vf_res(struct ice_vf *vf)
{
	struct ice_pf *pf = vf->pf;
	int i, last_vector_idx;

	/* First, disable VF's configuration API to prevent OS from
	 * accessing the VF's VSI after it's freed or invalidated.
	 */
	clear_bit(ICE_VF_STATE_INIT, vf->vf_states);

	/* free VSI and disconnect it from the parent uplink */
	if (vf->lan_vsi_idx) {
		ice_vsi_release(pf->vsi[vf->lan_vsi_idx]);
		vf->lan_vsi_idx = 0;
		vf->lan_vsi_num = 0;
		vf->num_mac = 0;
	}

	last_vector_idx = vf->first_vector_idx + pf->num_vf_msix - 1;
	/* Disable interrupts so that VF starts in a known state */
	for (i = vf->first_vector_idx; i <= last_vector_idx; i++) {
		wr32(&pf->hw, GLINT_DYN_CTL(i), GLINT_DYN_CTL_CLEARPBA_M);
		ice_flush(&pf->hw);
	}
	/* reset some of the state variables keeping track of the resources */
	clear_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states);
	clear_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states);
}