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
struct ice_hw {scalar_t__ port_info; int /*<<< orphan*/  mailboxq; } ;
struct ice_pf {int num_alloc_vfs; int /*<<< orphan*/  state; int /*<<< orphan*/ * vf; struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_PREPARED_FOR_RESET ; 
 scalar_t__ ice_check_sq_alive (struct ice_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_clear_hw_tbls (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_pf_dis_all_vsi (struct ice_pf*,int) ; 
 int /*<<< orphan*/  ice_sched_clear_port (scalar_t__) ; 
 int /*<<< orphan*/  ice_set_vf_state_qs_dis (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_shutdown_all_ctrlq (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_vc_notify_reset (struct ice_pf*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ice_prepare_for_reset(struct ice_pf *pf)
{
	struct ice_hw *hw = &pf->hw;
	int i;

	/* already prepared for reset */
	if (test_bit(__ICE_PREPARED_FOR_RESET, pf->state))
		return;

	/* Notify VFs of impending reset */
	if (ice_check_sq_alive(hw, &hw->mailboxq))
		ice_vc_notify_reset(pf);

	/* Disable VFs until reset is completed */
	for (i = 0; i < pf->num_alloc_vfs; i++)
		ice_set_vf_state_qs_dis(&pf->vf[i]);

	/* clear SW filtering DB */
	ice_clear_hw_tbls(hw);
	/* disable the VSIs and their queues that are not already DOWN */
	ice_pf_dis_all_vsi(pf, false);

	if (hw->port_info)
		ice_sched_clear_port(hw->port_info);

	ice_shutdown_all_ctrlq(hw);

	set_bit(__ICE_PREPARED_FOR_RESET, pf->state);
}