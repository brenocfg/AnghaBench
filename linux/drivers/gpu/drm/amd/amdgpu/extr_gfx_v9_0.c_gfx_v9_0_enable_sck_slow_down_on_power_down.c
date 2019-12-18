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
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RLC_PG_CNTL ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_CLK_SLOWDOWN_ON_PD_ENABLE ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmRLC_PG_CNTL ; 

__attribute__((used)) static void gfx_v9_0_enable_sck_slow_down_on_power_down(struct amdgpu_device *adev,
						bool enable)
{
	uint32_t data = 0;
	uint32_t default_data = 0;

	default_data = data = RREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_CNTL));
	data = REG_SET_FIELD(data, RLC_PG_CNTL,
			     SMU_CLK_SLOWDOWN_ON_PD_ENABLE,
			     enable ? 1 : 0);
	if(default_data != data)
		WREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_CNTL), data);
}