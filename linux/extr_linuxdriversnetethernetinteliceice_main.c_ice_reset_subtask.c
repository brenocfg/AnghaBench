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
struct ice_pf {int /*<<< orphan*/  state; int /*<<< orphan*/  hw; } ;
typedef  enum ice_reset_req { ____Placeholder_ice_reset_req } ice_reset_req ;

/* Variables and functions */
 int ICE_RESET_CORER ; 
 int ICE_RESET_GLOBR ; 
 int ICE_RESET_PFR ; 
 int /*<<< orphan*/  __ICE_CFG_BUSY ; 
 int /*<<< orphan*/  __ICE_CORER_RECV ; 
 int /*<<< orphan*/  __ICE_CORER_REQ ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  __ICE_GLOBR_RECV ; 
 int /*<<< orphan*/  __ICE_GLOBR_REQ ; 
 int /*<<< orphan*/  __ICE_PFR_REQ ; 
 int /*<<< orphan*/  __ICE_RESET_FAILED ; 
 int /*<<< orphan*/  __ICE_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_check_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_do_reset (struct ice_pf*,int) ; 
 scalar_t__ ice_is_reset_recovery_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_prepare_for_reset (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_rebuild (struct ice_pf*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_reset_subtask(struct ice_pf *pf)
{
	enum ice_reset_req reset_type;

	rtnl_lock();

	/* When a CORER/GLOBR/EMPR is about to happen, the hardware triggers an
	 * OICR interrupt. The OICR handler (ice_misc_intr) determines what
	 * type of reset happened and sets __ICE_RESET_RECOVERY_PENDING bit in
	 * pf->state. So if reset/recovery is pending (as indicated by this bit)
	 * we do a rebuild and return.
	 */
	if (ice_is_reset_recovery_pending(pf->state)) {
		clear_bit(__ICE_GLOBR_RECV, pf->state);
		clear_bit(__ICE_CORER_RECV, pf->state);
		ice_prepare_for_reset(pf);

		/* make sure we are ready to rebuild */
		if (ice_check_reset(&pf->hw))
			set_bit(__ICE_RESET_FAILED, pf->state);
		else
			ice_rebuild(pf);
		clear_bit(__ICE_RESET_RECOVERY_PENDING, pf->state);
		goto unlock;
	}

	/* No pending resets to finish processing. Check for new resets */
	if (test_and_clear_bit(__ICE_GLOBR_REQ, pf->state))
		reset_type = ICE_RESET_GLOBR;
	else if (test_and_clear_bit(__ICE_CORER_REQ, pf->state))
		reset_type = ICE_RESET_CORER;
	else if (test_and_clear_bit(__ICE_PFR_REQ, pf->state))
		reset_type = ICE_RESET_PFR;
	else
		goto unlock;

	/* reset if not already down or resetting */
	if (!test_bit(__ICE_DOWN, pf->state) &&
	    !test_bit(__ICE_CFG_BUSY, pf->state)) {
		ice_do_reset(pf, reset_type);
	}

unlock:
	rtnl_unlock();
}