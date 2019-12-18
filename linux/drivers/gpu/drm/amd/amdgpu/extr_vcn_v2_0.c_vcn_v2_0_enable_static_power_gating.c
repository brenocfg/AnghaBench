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
typedef  int uint32_t ;
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_VCN ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_WAIT_ON_RREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDIR_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDB_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDC_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDE_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDF_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDIL_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDIR_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDM_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDTD_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDTE_PWR_STATUS__SHIFT ; 
 int UVD_PGFSM_STATUS__UVDU_PWR_STATUS__SHIFT ; 
 int UVD_POWER_STATUS__UVD_POWER_STATUS_MASK ; 
 int UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmUVD_PGFSM_CONFIG ; 
 int /*<<< orphan*/  mmUVD_PGFSM_STATUS ; 
 int /*<<< orphan*/  mmUVD_POWER_STATUS ; 

__attribute__((used)) static void vcn_v2_0_enable_static_power_gating(struct amdgpu_device *adev)
{
	uint32_t data = 0;
	int ret;

	if (adev->pg_flags & AMD_PG_SUPPORT_VCN) {
		/* Before power off, this indicator has to be turned on */
		data = RREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS);
		data &= ~UVD_POWER_STATUS__UVD_POWER_STATUS_MASK;
		data |= UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF;
		WREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS, data);


		data = (2 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIR_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT);

		WREG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);

		data = (2 << UVD_PGFSM_STATUS__UVDM_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDU_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDF_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDC_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDB_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDIL_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDIR_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTD_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTE_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDE_PWR_STATUS__SHIFT);
		SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_PGFSM_STATUS, data, 0xFFFFF, ret);
	}
}