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
 int /*<<< orphan*/  SOC15_WAIT_ON_RREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDIR_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON ; 
 int UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT ; 
 int UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT ; 
 int /*<<< orphan*/  UVD_PGFSM_STATUS__UVDM_UVDU_PWR_ON_2_0 ; 
 int UVD_POWER_STATUS__UVD_PG_EN_MASK ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmUVD_PGFSM_CONFIG ; 
 int /*<<< orphan*/  mmUVD_PGFSM_STATUS ; 
 int /*<<< orphan*/  mmUVD_POWER_STATUS ; 

__attribute__((used)) static void vcn_v2_0_disable_static_power_gating(struct amdgpu_device *adev)
{
	uint32_t data = 0;
	int ret;

	if (adev->pg_flags & AMD_PG_SUPPORT_VCN) {
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIR_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT);

		WREG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_PGFSM_STATUS,
			UVD_PGFSM_STATUS__UVDM_UVDU_PWR_ON_2_0, 0xFFFFF, ret);
	} else {
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDIR_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT);
		WREG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_PGFSM_STATUS, 0,  0xFFFFF, ret);
	}

	/* polling UVD_PGFSM_STATUS to confirm UVDM_PWR_STATUS,
	 * UVDU_PWR_STATUS are 0 (power on) */

	data = RREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS);
	data &= ~0x103;
	if (adev->pg_flags & AMD_PG_SUPPORT_VCN)
		data |= UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON |
			UVD_POWER_STATUS__UVD_PG_EN_MASK;

	WREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS, data);
}