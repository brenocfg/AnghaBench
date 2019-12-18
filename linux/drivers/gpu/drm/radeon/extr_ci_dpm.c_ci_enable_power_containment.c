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
struct TYPE_4__ {struct radeon_cac_tdp_table* cac_tdp_table; } ;
struct TYPE_5__ {TYPE_1__ dyn_state; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct radeon_cac_tdp_table {int maximum_power_delivery_limit; } ;
struct ci_power_info {int power_containment_features; scalar_t__ caps_power_containment; scalar_t__ enable_pkg_pwr_tracking_feature; scalar_t__ enable_tdc_limit_feature; scalar_t__ enable_bapm_feature; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int POWERCONTAINMENT_FEATURE_BAPM ; 
 int POWERCONTAINMENT_FEATURE_PkgPwrLimit ; 
 int POWERCONTAINMENT_FEATURE_TDCLimit ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableDTE ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableDTE ; 
 int /*<<< orphan*/  PPSMC_MSG_PkgPwrLimitDisable ; 
 int /*<<< orphan*/  PPSMC_MSG_PkgPwrLimitEnable ; 
 int /*<<< orphan*/  PPSMC_MSG_TDCLimitDisable ; 
 int /*<<< orphan*/  PPSMC_MSG_TDCLimitEnable ; 
 scalar_t__ PPSMC_Result_OK ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 scalar_t__ ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_set_power_limit (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_enable_power_containment(struct radeon_device *rdev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	PPSMC_Result smc_result;
	int ret = 0;

	if (enable) {
		pi->power_containment_features = 0;
		if (pi->caps_power_containment) {
			if (pi->enable_bapm_feature) {
				smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_EnableDTE);
				if (smc_result != PPSMC_Result_OK)
					ret = -EINVAL;
				else
					pi->power_containment_features |= POWERCONTAINMENT_FEATURE_BAPM;
			}

			if (pi->enable_tdc_limit_feature) {
				smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_TDCLimitEnable);
				if (smc_result != PPSMC_Result_OK)
					ret = -EINVAL;
				else
					pi->power_containment_features |= POWERCONTAINMENT_FEATURE_TDCLimit;
			}

			if (pi->enable_pkg_pwr_tracking_feature) {
				smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_PkgPwrLimitEnable);
				if (smc_result != PPSMC_Result_OK) {
					ret = -EINVAL;
				} else {
					struct radeon_cac_tdp_table *cac_tdp_table =
						rdev->pm.dpm.dyn_state.cac_tdp_table;
					u32 default_pwr_limit =
						(u32)(cac_tdp_table->maximum_power_delivery_limit * 256);

					pi->power_containment_features |= POWERCONTAINMENT_FEATURE_PkgPwrLimit;

					ci_set_power_limit(rdev, default_pwr_limit);
				}
			}
		}
	} else {
		if (pi->caps_power_containment && pi->power_containment_features) {
			if (pi->power_containment_features & POWERCONTAINMENT_FEATURE_TDCLimit)
				ci_send_msg_to_smc(rdev, PPSMC_MSG_TDCLimitDisable);

			if (pi->power_containment_features & POWERCONTAINMENT_FEATURE_BAPM)
				ci_send_msg_to_smc(rdev, PPSMC_MSG_DisableDTE);

			if (pi->power_containment_features & POWERCONTAINMENT_FEATURE_PkgPwrLimit)
				ci_send_msg_to_smc(rdev, PPSMC_MSG_PkgPwrLimitDisable);
			pi->power_containment_features = 0;
		}
	}

	return ret;
}