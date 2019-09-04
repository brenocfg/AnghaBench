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
struct TYPE_4__ {struct kv_power_info* priv; } ;
struct TYPE_5__ {TYPE_1__ dpm; } ;
struct radeon_device {scalar_t__ family; TYPE_3__* pdev; TYPE_2__ pm; } ;
struct kv_power_info {int enable_nb_dpm; int caps_power_containment; int caps_cac; int enable_didt; int caps_sq_ramping; int caps_db_ramping; int caps_td_ramping; int caps_tcp_ramping; int caps_sclk_ds; int enable_auto_thermal_throttling; int disable_nb_ps3_in_battery; int bapm_enable; int caps_sclk_throttle_low_notification; int caps_fps; int caps_uvd_pg; int caps_uvd_dpm; int caps_vce_pg; int caps_samu_pg; int caps_acp_pg; int caps_stable_p_state; int enable_dpm; scalar_t__ voltage_drop_t; int /*<<< orphan*/  sram_end; int /*<<< orphan*/ * at; } ;
struct TYPE_6__ {int subsystem_vendor; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int SUMO_MAX_HARDWARE_POWERLEVELS ; 
 int /*<<< orphan*/  TRINITY_AT_DFLT ; 
 int /*<<< orphan*/  kv_construct_boot_state (struct radeon_device*) ; 
 int kv_parse_power_table (struct radeon_device*) ; 
 int kv_parse_sys_info_table (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_patch_voltage_values (struct radeon_device*) ; 
 struct kv_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int r600_get_platform_caps (struct radeon_device*) ; 
 int r600_parse_extended_power_table (struct radeon_device*) ; 
 int radeon_bapm ; 

int kv_dpm_init(struct radeon_device *rdev)
{
	struct kv_power_info *pi;
	int ret, i;

	pi = kzalloc(sizeof(struct kv_power_info), GFP_KERNEL);
	if (pi == NULL)
		return -ENOMEM;
	rdev->pm.dpm.priv = pi;

	ret = r600_get_platform_caps(rdev);
	if (ret)
		return ret;

	ret = r600_parse_extended_power_table(rdev);
	if (ret)
		return ret;

	for (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++)
		pi->at[i] = TRINITY_AT_DFLT;

	pi->sram_end = SMC_RAM_END;

	/* Enabling nb dpm on an asrock system prevents dpm from working */
	if (rdev->pdev->subsystem_vendor == 0x1849)
		pi->enable_nb_dpm = false;
	else
		pi->enable_nb_dpm = true;

	pi->caps_power_containment = true;
	pi->caps_cac = true;
	pi->enable_didt = false;
	if (pi->enable_didt) {
		pi->caps_sq_ramping = true;
		pi->caps_db_ramping = true;
		pi->caps_td_ramping = true;
		pi->caps_tcp_ramping = true;
	}

	pi->caps_sclk_ds = true;
	pi->enable_auto_thermal_throttling = true;
	pi->disable_nb_ps3_in_battery = false;
	if (radeon_bapm == -1) {
		/* only enable bapm on KB, ML by default */
		if (rdev->family == CHIP_KABINI || rdev->family == CHIP_MULLINS)
			pi->bapm_enable = true;
		else
			pi->bapm_enable = false;
	} else if (radeon_bapm == 0) {
		pi->bapm_enable = false;
	} else {
		pi->bapm_enable = true;
	}
	pi->voltage_drop_t = 0;
	pi->caps_sclk_throttle_low_notification = false;
	pi->caps_fps = false; /* true? */
	pi->caps_uvd_pg = true;
	pi->caps_uvd_dpm = true;
	pi->caps_vce_pg = false; /* XXX true */
	pi->caps_samu_pg = false;
	pi->caps_acp_pg = false;
	pi->caps_stable_p_state = false;

	ret = kv_parse_sys_info_table(rdev);
	if (ret)
		return ret;

	kv_patch_voltage_values(rdev);
	kv_construct_boot_state(rdev);

	ret = kv_parse_power_table(rdev);
	if (ret)
		return ret;

	pi->enable_dpm = true;

	return 0;
}