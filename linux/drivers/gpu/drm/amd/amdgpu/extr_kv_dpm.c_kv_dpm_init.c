#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kv_power_info {int enable_nb_dpm; int caps_power_containment; int caps_cac; int enable_didt; int caps_sq_ramping; int caps_db_ramping; int caps_td_ramping; int caps_tcp_ramping; int caps_sclk_ds; int enable_auto_thermal_throttling; int disable_nb_ps3_in_battery; int bapm_enable; int caps_sclk_throttle_low_notification; int caps_fps; int caps_uvd_pg; int caps_uvd_dpm; int caps_vce_pg; int caps_samu_pg; int caps_acp_pg; int caps_stable_p_state; int enable_dpm; scalar_t__ voltage_drop_t; int /*<<< orphan*/  sram_end; int /*<<< orphan*/ * at; } ;
struct TYPE_3__ {struct kv_power_info* priv; } ;
struct TYPE_4__ {int pp_feature; TYPE_1__ dpm; } ;
struct amdgpu_device {int pg_flags; TYPE_2__ pm; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_ACP ; 
 int AMD_PG_SUPPORT_SAMU ; 
 int AMD_PG_SUPPORT_UVD ; 
 int AMD_PG_SUPPORT_VCE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PP_SCLK_DEEP_SLEEP_MASK ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int SUMO_MAX_HARDWARE_POWERLEVELS ; 
 int /*<<< orphan*/  TRINITY_AT_DFLT ; 
 scalar_t__ amdgpu_bapm ; 
 int amdgpu_get_platform_caps (struct amdgpu_device*) ; 
 int amdgpu_parse_extended_power_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_construct_boot_state (struct amdgpu_device*) ; 
 int kv_parse_power_table (struct amdgpu_device*) ; 
 int kv_parse_sys_info_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_patch_voltage_values (struct amdgpu_device*) ; 
 struct kv_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_dpm_init(struct amdgpu_device *adev)
{
	struct kv_power_info *pi;
	int ret, i;

	pi = kzalloc(sizeof(struct kv_power_info), GFP_KERNEL);
	if (pi == NULL)
		return -ENOMEM;
	adev->pm.dpm.priv = pi;

	ret = amdgpu_get_platform_caps(adev);
	if (ret)
		return ret;

	ret = amdgpu_parse_extended_power_table(adev);
	if (ret)
		return ret;

	for (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++)
		pi->at[i] = TRINITY_AT_DFLT;

	pi->sram_end = SMC_RAM_END;

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

	if (adev->pm.pp_feature & PP_SCLK_DEEP_SLEEP_MASK)
		pi->caps_sclk_ds = true;
	else
		pi->caps_sclk_ds = false;

	pi->enable_auto_thermal_throttling = true;
	pi->disable_nb_ps3_in_battery = false;
	if (amdgpu_bapm == 0)
		pi->bapm_enable = false;
	else
		pi->bapm_enable = true;
	pi->voltage_drop_t = 0;
	pi->caps_sclk_throttle_low_notification = false;
	pi->caps_fps = false; /* true? */
	pi->caps_uvd_pg = (adev->pg_flags & AMD_PG_SUPPORT_UVD) ? true : false;
	pi->caps_uvd_dpm = true;
	pi->caps_vce_pg = (adev->pg_flags & AMD_PG_SUPPORT_VCE) ? true : false;
	pi->caps_samu_pg = (adev->pg_flags & AMD_PG_SUPPORT_SAMU) ? true : false;
	pi->caps_acp_pg = (adev->pg_flags & AMD_PG_SUPPORT_ACP) ? true : false;
	pi->caps_stable_p_state = false;

	ret = kv_parse_sys_info_table(adev);
	if (ret)
		return ret;

	kv_patch_voltage_values(adev);
	kv_construct_boot_state(adev);

	ret = kv_parse_power_table(adev);
	if (ret)
		return ret;

	pi->enable_dpm = true;

	return 0;
}