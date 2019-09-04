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
struct i40e_hw {scalar_t__ revision_id; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_RESET_FAILED ; 
 int /*<<< orphan*/  I40E_GLGEN_RSTAT ; 
 int I40E_GLGEN_RSTAT_DEVSTATE_MASK ; 
 int /*<<< orphan*/  I40E_GLGEN_RSTCTL ; 
 int I40E_GLGEN_RSTCTL_GRSTDEL_MASK ; 
 int I40E_GLGEN_RSTCTL_GRSTDEL_SHIFT ; 
 int /*<<< orphan*/  I40E_GLNVM_ULD ; 
 int I40E_GLNVM_ULD_CONF_CORE_DONE_MASK ; 
 int I40E_GLNVM_ULD_CONF_GLOBAL_DONE_MASK ; 
 int /*<<< orphan*/  I40E_PFGEN_CTRL ; 
 int I40E_PFGEN_CTRL_PFSWR_MASK ; 
 int I40E_PF_RESET_WAIT_COUNT ; 
 int I40E_PF_RESET_WAIT_COUNT_A0 ; 
 int /*<<< orphan*/  hw_dbg (struct i40e_hw*,char*,...) ; 
 int /*<<< orphan*/  i40e_clear_pxe_mode (struct i40e_hw*) ; 
 scalar_t__ i40e_poll_globr (struct i40e_hw*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

i40e_status i40e_pf_reset(struct i40e_hw *hw)
{
	u32 cnt = 0;
	u32 cnt1 = 0;
	u32 reg = 0;
	u32 grst_del;

	/* Poll for Global Reset steady state in case of recent GRST.
	 * The grst delay value is in 100ms units, and we'll wait a
	 * couple counts longer to be sure we don't just miss the end.
	 */
	grst_del = (rd32(hw, I40E_GLGEN_RSTCTL) &
		    I40E_GLGEN_RSTCTL_GRSTDEL_MASK) >>
		    I40E_GLGEN_RSTCTL_GRSTDEL_SHIFT;

	/* It can take upto 15 secs for GRST steady state.
	 * Bump it to 16 secs max to be safe.
	 */
	grst_del = grst_del * 20;

	for (cnt = 0; cnt < grst_del; cnt++) {
		reg = rd32(hw, I40E_GLGEN_RSTAT);
		if (!(reg & I40E_GLGEN_RSTAT_DEVSTATE_MASK))
			break;
		msleep(100);
	}
	if (reg & I40E_GLGEN_RSTAT_DEVSTATE_MASK) {
		hw_dbg(hw, "Global reset polling failed to complete.\n");
		return I40E_ERR_RESET_FAILED;
	}

	/* Now Wait for the FW to be ready */
	for (cnt1 = 0; cnt1 < I40E_PF_RESET_WAIT_COUNT; cnt1++) {
		reg = rd32(hw, I40E_GLNVM_ULD);
		reg &= (I40E_GLNVM_ULD_CONF_CORE_DONE_MASK |
			I40E_GLNVM_ULD_CONF_GLOBAL_DONE_MASK);
		if (reg == (I40E_GLNVM_ULD_CONF_CORE_DONE_MASK |
			    I40E_GLNVM_ULD_CONF_GLOBAL_DONE_MASK)) {
			hw_dbg(hw, "Core and Global modules ready %d\n", cnt1);
			break;
		}
		usleep_range(10000, 20000);
	}
	if (!(reg & (I40E_GLNVM_ULD_CONF_CORE_DONE_MASK |
		     I40E_GLNVM_ULD_CONF_GLOBAL_DONE_MASK))) {
		hw_dbg(hw, "wait for FW Reset complete timedout\n");
		hw_dbg(hw, "I40E_GLNVM_ULD = 0x%x\n", reg);
		return I40E_ERR_RESET_FAILED;
	}

	/* If there was a Global Reset in progress when we got here,
	 * we don't need to do the PF Reset
	 */
	if (!cnt) {
		u32 reg2 = 0;
		if (hw->revision_id == 0)
			cnt = I40E_PF_RESET_WAIT_COUNT_A0;
		else
			cnt = I40E_PF_RESET_WAIT_COUNT;
		reg = rd32(hw, I40E_PFGEN_CTRL);
		wr32(hw, I40E_PFGEN_CTRL,
		     (reg | I40E_PFGEN_CTRL_PFSWR_MASK));
		for (; cnt; cnt--) {
			reg = rd32(hw, I40E_PFGEN_CTRL);
			if (!(reg & I40E_PFGEN_CTRL_PFSWR_MASK))
				break;
			reg2 = rd32(hw, I40E_GLGEN_RSTAT);
			if (reg2 & I40E_GLGEN_RSTAT_DEVSTATE_MASK)
				break;
			usleep_range(1000, 2000);
		}
		if (reg2 & I40E_GLGEN_RSTAT_DEVSTATE_MASK) {
			if (i40e_poll_globr(hw, grst_del))
				return I40E_ERR_RESET_FAILED;
		} else if (reg & I40E_PFGEN_CTRL_PFSWR_MASK) {
			hw_dbg(hw, "PF reset polling failed to complete.\n");
			return I40E_ERR_RESET_FAILED;
		}
	}

	i40e_clear_pxe_mode(hw);

	return 0;
}