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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD_BALANCE_ENABLE ; 
 int /*<<< orphan*/  RLC_LB_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v6_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  mmSPI_LB_CU_MASK ; 

__attribute__((used)) static void gfx_v6_0_enable_lbpw(struct amdgpu_device *adev, bool enable)
{
	WREG32_FIELD(RLC_LB_CNTL, LOAD_BALANCE_ENABLE, enable ? 1 : 0);

	if (!enable) {
		gfx_v6_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		WREG32(mmSPI_LB_CU_MASK, 0x00ff);
	}
}