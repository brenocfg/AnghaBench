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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  suspend_err; } ;
struct TYPE_5__ {int is_suspended; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {scalar_t__ is_allowed; int /*<<< orphan*/  resume_work; int /*<<< orphan*/  suspend_work; } ;
struct ufs_hba {int pm_op_in_progress; int rpm_lvl; int spm_lvl; int curr_dev_pwr_mode; int uic_link_state; TYPE_3__ ufs_stats; TYPE_2__ clk_gating; TYPE_1__ clk_scaling; int /*<<< orphan*/  dev; int /*<<< orphan*/  auto_bkops_enabled; } ;
typedef  enum uic_link_state { ____Placeholder_uic_link_state } uic_link_state ;
typedef  enum ufs_pm_op { ____Placeholder_ufs_pm_op } ufs_pm_op ;
typedef  enum ufs_pm_level { ____Placeholder_ufs_pm_level } ufs_pm_level ;
typedef  enum ufs_dev_pwr_mode { ____Placeholder_ufs_dev_pwr_mode } ufs_dev_pwr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CLKS_OFF ; 
 int EINVAL ; 
 int UFS_ACTIVE_PWR_MODE ; 
 int UFS_POWERDOWN_PWR_MODE ; 
 int UIC_LINK_ACTIVE_STATE ; 
 int UIC_LINK_OFF_STATE ; 
 int /*<<< orphan*/  __ufshcd_setup_clocks (struct ufs_hba*,int,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ufshcd_clk_gating (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ufs_get_pm_lvl_to_dev_pwr_mode (int) ; 
 int ufs_get_pm_lvl_to_link_pwr_state (int) ; 
 scalar_t__ ufshcd_can_autobkops_during_suspend (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_disable_auto_bkops (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_disable_irq (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_hba_vreg_set_lpm (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_hold (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_host_reset_and_restore (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_is_link_active (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_link_hibern8 (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_link_off (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_runtime_pm (int) ; 
 int /*<<< orphan*/  ufshcd_is_shutdown_pm (int) ; 
 int /*<<< orphan*/  ufshcd_is_ufs_dev_active (struct ufs_hba*) ; 
 int ufshcd_link_state_transition (struct ufs_hba*,int,int) ; 
 int /*<<< orphan*/  ufshcd_release (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_resume_clkscaling (struct ufs_hba*) ; 
 int ufshcd_set_dev_pwr_mode (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_set_link_active (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_setup_clocks (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_suspend_clkscaling (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_uic_hibern8_exit (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_update_reg_hist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ufshcd_urgent_bkops (struct ufs_hba*) ; 
 int ufshcd_vops_suspend (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_vreg_set_hpm (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_vreg_set_lpm (struct ufs_hba*) ; 

__attribute__((used)) static int ufshcd_suspend(struct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	int ret = 0;
	enum ufs_pm_level pm_lvl;
	enum ufs_dev_pwr_mode req_dev_pwr_mode;
	enum uic_link_state req_link_state;

	hba->pm_op_in_progress = 1;
	if (!ufshcd_is_shutdown_pm(pm_op)) {
		pm_lvl = ufshcd_is_runtime_pm(pm_op) ?
			 hba->rpm_lvl : hba->spm_lvl;
		req_dev_pwr_mode = ufs_get_pm_lvl_to_dev_pwr_mode(pm_lvl);
		req_link_state = ufs_get_pm_lvl_to_link_pwr_state(pm_lvl);
	} else {
		req_dev_pwr_mode = UFS_POWERDOWN_PWR_MODE;
		req_link_state = UIC_LINK_OFF_STATE;
	}

	/*
	 * If we can't transition into any of the low power modes
	 * just gate the clocks.
	 */
	ufshcd_hold(hba, false);
	hba->clk_gating.is_suspended = true;

	if (hba->clk_scaling.is_allowed) {
		cancel_work_sync(&hba->clk_scaling.suspend_work);
		cancel_work_sync(&hba->clk_scaling.resume_work);
		ufshcd_suspend_clkscaling(hba);
	}

	if (req_dev_pwr_mode == UFS_ACTIVE_PWR_MODE &&
			req_link_state == UIC_LINK_ACTIVE_STATE) {
		goto disable_clks;
	}

	if ((req_dev_pwr_mode == hba->curr_dev_pwr_mode) &&
	    (req_link_state == hba->uic_link_state))
		goto enable_gating;

	/* UFS device & link must be active before we enter in this function */
	if (!ufshcd_is_ufs_dev_active(hba) || !ufshcd_is_link_active(hba)) {
		ret = -EINVAL;
		goto enable_gating;
	}

	if (ufshcd_is_runtime_pm(pm_op)) {
		if (ufshcd_can_autobkops_during_suspend(hba)) {
			/*
			 * The device is idle with no requests in the queue,
			 * allow background operations if bkops status shows
			 * that performance might be impacted.
			 */
			ret = ufshcd_urgent_bkops(hba);
			if (ret)
				goto enable_gating;
		} else {
			/* make sure that auto bkops is disabled */
			ufshcd_disable_auto_bkops(hba);
		}
	}

	if ((req_dev_pwr_mode != hba->curr_dev_pwr_mode) &&
	     ((ufshcd_is_runtime_pm(pm_op) && !hba->auto_bkops_enabled) ||
	       !ufshcd_is_runtime_pm(pm_op))) {
		/* ensure that bkops is disabled */
		ufshcd_disable_auto_bkops(hba);
		ret = ufshcd_set_dev_pwr_mode(hba, req_dev_pwr_mode);
		if (ret)
			goto enable_gating;
	}

	ret = ufshcd_link_state_transition(hba, req_link_state, 1);
	if (ret)
		goto set_dev_active;

	ufshcd_vreg_set_lpm(hba);

disable_clks:
	/*
	 * Call vendor specific suspend callback. As these callbacks may access
	 * vendor specific host controller register space call them before the
	 * host clocks are ON.
	 */
	ret = ufshcd_vops_suspend(hba, pm_op);
	if (ret)
		goto set_link_active;

	if (!ufshcd_is_link_active(hba))
		ufshcd_setup_clocks(hba, false);
	else
		/* If link is active, device ref_clk can't be switched off */
		__ufshcd_setup_clocks(hba, false, true);

	hba->clk_gating.state = CLKS_OFF;
	trace_ufshcd_clk_gating(dev_name(hba->dev), hba->clk_gating.state);
	/*
	 * Disable the host irq as host controller as there won't be any
	 * host controller transaction expected till resume.
	 */
	ufshcd_disable_irq(hba);
	/* Put the host controller in low power mode if possible */
	ufshcd_hba_vreg_set_lpm(hba);
	goto out;

set_link_active:
	if (hba->clk_scaling.is_allowed)
		ufshcd_resume_clkscaling(hba);
	ufshcd_vreg_set_hpm(hba);
	if (ufshcd_is_link_hibern8(hba) && !ufshcd_uic_hibern8_exit(hba))
		ufshcd_set_link_active(hba);
	else if (ufshcd_is_link_off(hba))
		ufshcd_host_reset_and_restore(hba);
set_dev_active:
	if (!ufshcd_set_dev_pwr_mode(hba, UFS_ACTIVE_PWR_MODE))
		ufshcd_disable_auto_bkops(hba);
enable_gating:
	if (hba->clk_scaling.is_allowed)
		ufshcd_resume_clkscaling(hba);
	hba->clk_gating.is_suspended = false;
	ufshcd_release(hba);
out:
	hba->pm_op_in_progress = 0;
	if (ret)
		ufshcd_update_reg_hist(&hba->ufs_stats.suspend_err, (u32)ret);
	return ret;
}