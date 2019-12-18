#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int reset_ongoing; } ;
struct ice_pf {int /*<<< orphan*/  state; TYPE_1__ hw; } ;
typedef  enum ice_reset_req { ____Placeholder_ice_reset_req } ice_reset_req ;

/* Variables and functions */
 int ICE_RESET_CORER ; 
 int ICE_RESET_EMPR ; 
 int ICE_RESET_GLOBR ; 
 int ICE_RESET_INVAL ; 
 int ICE_RESET_PFR ; 
 int /*<<< orphan*/  __ICE_CFG_BUSY ; 
 int /*<<< orphan*/  __ICE_CORER_RECV ; 
 int /*<<< orphan*/  __ICE_CORER_REQ ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  __ICE_EMPR_RECV ; 
 int /*<<< orphan*/  __ICE_GLOBR_RECV ; 
 int /*<<< orphan*/  __ICE_GLOBR_REQ ; 
 int /*<<< orphan*/  __ICE_PFR_REQ ; 
 int /*<<< orphan*/  __ICE_PREPARED_FOR_RESET ; 
 int /*<<< orphan*/  __ICE_RESET_FAILED ; 
 int /*<<< orphan*/  __ICE_RESET_OICR_RECV ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_check_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  ice_do_reset (struct ice_pf*,int) ; 
 int /*<<< orphan*/  ice_prepare_for_reset (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_rebuild (struct ice_pf*,int) ; 
 int /*<<< orphan*/  ice_reset_all_vfs (struct ice_pf*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_reset_subtask(struct ice_pf *pf)
{
	enum ice_reset_req reset_type = ICE_RESET_INVAL;

	/* When a CORER/GLOBR/EMPR is about to happen, the hardware triggers an
	 * OICR interrupt. The OICR handler (ice_misc_intr) determines what type
	 * of reset is pending and sets bits in pf->state indicating the reset
	 * type and __ICE_RESET_OICR_RECV. So, if the latter bit is set
	 * prepare for pending reset if not already (for PF software-initiated
	 * global resets the software should already be prepared for it as
	 * indicated by __ICE_PREPARED_FOR_RESET; for global resets initiated
	 * by firmware or software on other PFs, that bit is not set so prepare
	 * for the reset now), poll for reset done, rebuild and return.
	 */
	if (test_bit(__ICE_RESET_OICR_RECV, pf->state)) {
		/* Perform the largest reset requested */
		if (test_and_clear_bit(__ICE_CORER_RECV, pf->state))
			reset_type = ICE_RESET_CORER;
		if (test_and_clear_bit(__ICE_GLOBR_RECV, pf->state))
			reset_type = ICE_RESET_GLOBR;
		if (test_and_clear_bit(__ICE_EMPR_RECV, pf->state))
			reset_type = ICE_RESET_EMPR;
		/* return if no valid reset type requested */
		if (reset_type == ICE_RESET_INVAL)
			return;
		ice_prepare_for_reset(pf);

		/* make sure we are ready to rebuild */
		if (ice_check_reset(&pf->hw)) {
			set_bit(__ICE_RESET_FAILED, pf->state);
		} else {
			/* done with reset. start rebuild */
			pf->hw.reset_ongoing = false;
			ice_rebuild(pf, reset_type);
			/* clear bit to resume normal operations, but
			 * ICE_NEEDS_RESTART bit is set in case rebuild failed
			 */
			clear_bit(__ICE_RESET_OICR_RECV, pf->state);
			clear_bit(__ICE_PREPARED_FOR_RESET, pf->state);
			clear_bit(__ICE_PFR_REQ, pf->state);
			clear_bit(__ICE_CORER_REQ, pf->state);
			clear_bit(__ICE_GLOBR_REQ, pf->state);
			ice_reset_all_vfs(pf, true);
		}

		return;
	}

	/* No pending resets to finish processing. Check for new resets */
	if (test_bit(__ICE_PFR_REQ, pf->state))
		reset_type = ICE_RESET_PFR;
	if (test_bit(__ICE_CORER_REQ, pf->state))
		reset_type = ICE_RESET_CORER;
	if (test_bit(__ICE_GLOBR_REQ, pf->state))
		reset_type = ICE_RESET_GLOBR;
	/* If no valid reset type requested just return */
	if (reset_type == ICE_RESET_INVAL)
		return;

	/* reset if not already down or busy */
	if (!test_bit(__ICE_DOWN, pf->state) &&
	    !test_bit(__ICE_CFG_BUSY, pf->state)) {
		ice_do_reset(pf, reset_type);
	}
}