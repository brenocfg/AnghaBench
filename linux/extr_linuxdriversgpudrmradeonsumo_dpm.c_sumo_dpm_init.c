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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  enable_boost; int /*<<< orphan*/  htc_tmp_lmt; } ;
struct sumo_power_info {int driver_nbps_policy_disable; int disable_gfx_power_gating_in_uvd; int enable_alt_vddnb; int enable_sclk_ds; int enable_dynamic_m3_arbiter; int enable_dynamic_patch_ps; int enable_gfx_power_gating; int enable_gfx_clock_gating; int enable_mg_clock_gating; int enable_auto_thermal_throttling; int enable_dpm; TYPE_3__ sys_info; int /*<<< orphan*/  enable_boost; int /*<<< orphan*/  thermal_auto_throttling; int /*<<< orphan*/  asi; int /*<<< orphan*/  pasi; } ;
struct TYPE_4__ {struct sumo_power_info* priv; } ;
struct TYPE_5__ {TYPE_1__ dpm; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ pm; } ;

/* Variables and functions */
 int ATI_REV_ID_MASK ; 
 int ATI_REV_ID_SHIFT ; 
 scalar_t__ CHIP_PALM ; 
 int /*<<< orphan*/  CYPRESS_HASI_DFLT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HW_REV ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RV770_ASI_DFLT ; 
 struct sumo_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int r600_get_platform_caps (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_construct_boot_and_acpi_state (struct radeon_device*) ; 
 int sumo_parse_power_table (struct radeon_device*) ; 
 int sumo_parse_sys_info_table (struct radeon_device*) ; 

int sumo_dpm_init(struct radeon_device *rdev)
{
	struct sumo_power_info *pi;
	u32 hw_rev = (RREG32(HW_REV) & ATI_REV_ID_MASK) >> ATI_REV_ID_SHIFT;
	int ret;

	pi = kzalloc(sizeof(struct sumo_power_info), GFP_KERNEL);
	if (pi == NULL)
		return -ENOMEM;
	rdev->pm.dpm.priv = pi;

	pi->driver_nbps_policy_disable = false;
	if ((rdev->family == CHIP_PALM) && (hw_rev < 3))
		pi->disable_gfx_power_gating_in_uvd = true;
	else
		pi->disable_gfx_power_gating_in_uvd = false;
	pi->enable_alt_vddnb = true;
	pi->enable_sclk_ds = true;
	pi->enable_dynamic_m3_arbiter = false;
	pi->enable_dynamic_patch_ps = true;
	/* Some PALM chips don't seem to properly ungate gfx when UVD is in use;
	 * for now just disable gfx PG.
	 */
	if (rdev->family == CHIP_PALM)
		pi->enable_gfx_power_gating = false;
	else
		pi->enable_gfx_power_gating = true;
	pi->enable_gfx_clock_gating = true;
	pi->enable_mg_clock_gating = true;
	pi->enable_auto_thermal_throttling = true;

	ret = sumo_parse_sys_info_table(rdev);
	if (ret)
		return ret;

	sumo_construct_boot_and_acpi_state(rdev);

	ret = r600_get_platform_caps(rdev);
	if (ret)
		return ret;

	ret = sumo_parse_power_table(rdev);
	if (ret)
		return ret;

	pi->pasi = CYPRESS_HASI_DFLT;
	pi->asi = RV770_ASI_DFLT;
	pi->thermal_auto_throttling = pi->sys_info.htc_tmp_lmt;
	pi->enable_boost = pi->sys_info.enable_boost;
	pi->enable_dpm = true;

	return 0;
}