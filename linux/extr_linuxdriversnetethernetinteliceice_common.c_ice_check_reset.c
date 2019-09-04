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
typedef  int u32 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GLGEN_RSTAT ; 
 int GLGEN_RSTAT_DEVSTATE_M ; 
 int /*<<< orphan*/  GLGEN_RSTCTL ; 
 int GLGEN_RSTCTL_GRSTDEL_M ; 
 int GLGEN_RSTCTL_GRSTDEL_S ; 
 int /*<<< orphan*/  GLNVM_ULD ; 
 int GLNVM_ULD_CORER_DONE_M ; 
 int GLNVM_ULD_GLOBR_DONE_M ; 
 int /*<<< orphan*/  ICE_DBG_INIT ; 
 int ICE_ERR_RESET_FAILED ; 
 int ICE_PF_RESET_WAIT_COUNT ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 

enum ice_status ice_check_reset(struct ice_hw *hw)
{
	u32 cnt, reg = 0, grst_delay;

	/* Poll for Device Active state in case a recent CORER, GLOBR,
	 * or EMPR has occurred. The grst delay value is in 100ms units.
	 * Add 1sec for outstanding AQ commands that can take a long time.
	 */
	grst_delay = ((rd32(hw, GLGEN_RSTCTL) & GLGEN_RSTCTL_GRSTDEL_M) >>
		      GLGEN_RSTCTL_GRSTDEL_S) + 10;

	for (cnt = 0; cnt < grst_delay; cnt++) {
		mdelay(100);
		reg = rd32(hw, GLGEN_RSTAT);
		if (!(reg & GLGEN_RSTAT_DEVSTATE_M))
			break;
	}

	if (cnt == grst_delay) {
		ice_debug(hw, ICE_DBG_INIT,
			  "Global reset polling failed to complete.\n");
		return ICE_ERR_RESET_FAILED;
	}

#define ICE_RESET_DONE_MASK	(GLNVM_ULD_CORER_DONE_M | \
				 GLNVM_ULD_GLOBR_DONE_M)

	/* Device is Active; check Global Reset processes are done */
	for (cnt = 0; cnt < ICE_PF_RESET_WAIT_COUNT; cnt++) {
		reg = rd32(hw, GLNVM_ULD) & ICE_RESET_DONE_MASK;
		if (reg == ICE_RESET_DONE_MASK) {
			ice_debug(hw, ICE_DBG_INIT,
				  "Global reset processes done. %d\n", cnt);
			break;
		}
		mdelay(10);
	}

	if (cnt == ICE_PF_RESET_WAIT_COUNT) {
		ice_debug(hw, ICE_DBG_INIT,
			  "Wait for Reset Done timed out. GLNVM_ULD = 0x%x\n",
			  reg);
		return ICE_ERR_RESET_FAILED;
	}

	return 0;
}