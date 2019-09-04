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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RLC_CNTL__RLC_ENABLE_F32_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v6_0_wait_for_rlc_serdes (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmRLC_CNTL ; 

__attribute__((used)) static u32 gfx_v6_0_halt_rlc(struct amdgpu_device *adev)
{
	u32 data, orig;

	orig = data = RREG32(mmRLC_CNTL);

	if (data & RLC_CNTL__RLC_ENABLE_F32_MASK) {
		data &= ~RLC_CNTL__RLC_ENABLE_F32_MASK;
		WREG32(mmRLC_CNTL, data);

		gfx_v6_0_wait_for_rlc_serdes(adev);
	}

	return orig;
}