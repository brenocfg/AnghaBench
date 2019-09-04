#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  htc_tmp_lmt; } ;
struct trinity_power_info {int enable_bapm; int enable_nbps_policy; int enable_sclk_ds; int enable_gfx_power_gating; int enable_gfx_clock_gating; int enable_mg_clock_gating; int enable_gfx_dynamic_mgpg; int override_dynamic_mgpg; int enable_auto_thermal_throttling; int voltage_drop_in_dce; int uvd_dpm; int enable_dpm; TYPE_4__ sys_info; int /*<<< orphan*/  thermal_auto_throttling; int /*<<< orphan*/ * at; } ;
struct TYPE_5__ {struct trinity_power_info* priv; } ;
struct TYPE_6__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_3__* pdev; TYPE_2__ pm; } ;
struct TYPE_7__ {int subsystem_vendor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SUMO_MAX_HARDWARE_POWERLEVELS ; 
 int /*<<< orphan*/  TRINITY_AT_DFLT ; 
 struct trinity_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int r600_get_platform_caps (struct radeon_device*) ; 
 int r600_parse_extended_power_table (struct radeon_device*) ; 
 int radeon_bapm ; 
 int /*<<< orphan*/  trinity_construct_boot_state (struct radeon_device*) ; 
 int trinity_parse_power_table (struct radeon_device*) ; 
 int trinity_parse_sys_info_table (struct radeon_device*) ; 

int trinity_dpm_init(struct radeon_device *rdev)
{
	struct trinity_power_info *pi;
	int ret, i;

	pi = kzalloc(sizeof(struct trinity_power_info), GFP_KERNEL);
	if (pi == NULL)
		return -ENOMEM;
	rdev->pm.dpm.priv = pi;

	for (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++)
		pi->at[i] = TRINITY_AT_DFLT;

	if (radeon_bapm == -1) {
		/* There are stability issues reported on with
		 * bapm enabled when switching between AC and battery
		 * power.  At the same time, some MSI boards hang
		 * if it's not enabled and dpm is enabled.  Just enable
		 * it for MSI boards right now.
		 */
		if (rdev->pdev->subsystem_vendor == 0x1462)
			pi->enable_bapm = true;
		else
			pi->enable_bapm = false;
	} else if (radeon_bapm == 0) {
		pi->enable_bapm = false;
	} else {
		pi->enable_bapm = true;
	}
	pi->enable_nbps_policy = true;
	pi->enable_sclk_ds = true;
	pi->enable_gfx_power_gating = true;
	pi->enable_gfx_clock_gating = true;
	pi->enable_mg_clock_gating = false;
	pi->enable_gfx_dynamic_mgpg = false;
	pi->override_dynamic_mgpg = false;
	pi->enable_auto_thermal_throttling = true;
	pi->voltage_drop_in_dce = false; /* need to restructure dpm/modeset interaction */
	pi->uvd_dpm = true; /* ??? */

	ret = trinity_parse_sys_info_table(rdev);
	if (ret)
		return ret;

	trinity_construct_boot_state(rdev);

	ret = r600_get_platform_caps(rdev);
	if (ret)
		return ret;

	ret = r600_parse_extended_power_table(rdev);
	if (ret)
		return ret;

	ret = trinity_parse_power_table(rdev);
	if (ret)
		return ret;

	pi->thermal_auto_throttling = pi->sys_info.htc_tmp_lmt;
	pi->enable_dpm = true;

	return 0;
}