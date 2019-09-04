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
typedef  int u32 ;
struct kv_ps {int dpm0_pg_nb_ps_lo; int dpm0_pg_nb_ps_hi; int dpmx_nb_ps_lo; int dpmx_nb_ps_hi; } ;
struct TYPE_2__ {scalar_t__ nb_dpm_enable; } ;
struct kv_power_info {TYPE_1__ sys_info; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int NB_DPM_CONFIG_1__Dpm0PgNbPsHi_MASK ; 
 int NB_DPM_CONFIG_1__Dpm0PgNbPsHi__SHIFT ; 
 int NB_DPM_CONFIG_1__Dpm0PgNbPsLo_MASK ; 
 int NB_DPM_CONFIG_1__Dpm0PgNbPsLo__SHIFT ; 
 int NB_DPM_CONFIG_1__DpmXNbPsHi_MASK ; 
 int NB_DPM_CONFIG_1__DpmXNbPsHi__SHIFT ; 
 int NB_DPM_CONFIG_1__DpmXNbPsLo_MASK ; 
 int NB_DPM_CONFIG_1__DpmXNbPsLo__SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixNB_DPM_CONFIG_1 ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 struct kv_ps* kv_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static void kv_program_nbps_index_settings(struct amdgpu_device *adev,
					   struct amdgpu_ps *new_rps)
{
	struct kv_ps *new_ps = kv_get_ps(new_rps);
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 nbdpmconfig1;

	if (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		return;

	if (pi->sys_info.nb_dpm_enable) {
		nbdpmconfig1 = RREG32_SMC(ixNB_DPM_CONFIG_1);
		nbdpmconfig1 &= ~(NB_DPM_CONFIG_1__Dpm0PgNbPsLo_MASK |
				NB_DPM_CONFIG_1__Dpm0PgNbPsHi_MASK |
				NB_DPM_CONFIG_1__DpmXNbPsLo_MASK |
				NB_DPM_CONFIG_1__DpmXNbPsHi_MASK);
		nbdpmconfig1 |= (new_ps->dpm0_pg_nb_ps_lo << NB_DPM_CONFIG_1__Dpm0PgNbPsLo__SHIFT) |
				(new_ps->dpm0_pg_nb_ps_hi << NB_DPM_CONFIG_1__Dpm0PgNbPsHi__SHIFT) |
				(new_ps->dpmx_nb_ps_lo << NB_DPM_CONFIG_1__DpmXNbPsLo__SHIFT) |
				(new_ps->dpmx_nb_ps_hi << NB_DPM_CONFIG_1__DpmXNbPsHi__SHIFT);
		WREG32_SMC(ixNB_DPM_CONFIG_1, nbdpmconfig1);
	}
}