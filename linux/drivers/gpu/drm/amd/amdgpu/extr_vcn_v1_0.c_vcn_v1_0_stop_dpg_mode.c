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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_WAIT_ON_RREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  UVD_POWER_STATUS__UVD_PG_MODE_MASK ; 
 int UVD_POWER_STATUS__UVD_POWER_STATUS_MASK ; 
 int UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_JRBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_POWER_STATUS ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RB_RPTR ; 
 int /*<<< orphan*/  mmUVD_RB_RPTR2 ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR2 ; 

__attribute__((used)) static int vcn_v1_0_stop_dpg_mode(struct amdgpu_device *adev)
{
	int ret_code = 0;
	uint32_t tmp;

	/* Wait for power status to be UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF */
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
			UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF,
			UVD_POWER_STATUS__UVD_POWER_STATUS_MASK, ret_code);

	/* wait for read ptr to be equal to write ptr */
	tmp = RREG32_SOC15(UVD, 0, mmUVD_RB_WPTR);
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_RB_RPTR, tmp, 0xFFFFFFFF, ret_code);

	tmp = RREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2);
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_RB_RPTR2, tmp, 0xFFFFFFFF, ret_code);

	tmp = RREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_WPTR);
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_JRBC_RB_RPTR, tmp, 0xFFFFFFFF, ret_code);

	tmp = RREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR) & 0x7FFFFFFF;
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_RBC_RB_RPTR, tmp, 0xFFFFFFFF, ret_code);

	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
		UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF,
		UVD_POWER_STATUS__UVD_POWER_STATUS_MASK, ret_code);

	/* disable dynamic power gating mode */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_POWER_STATUS), 0,
			~UVD_POWER_STATUS__UVD_PG_MODE_MASK);

	return 0;
}