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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 scalar_t__ REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RLC_CNTL ; 
 int /*<<< orphan*/  RLC_ENABLE_F32 ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmRLC_CNTL ; 

__attribute__((used)) static bool gfx_v10_0_is_rlc_enabled(struct amdgpu_device *adev)
{
	uint32_t rlc_cntl;

	/* if RLC is not enabled, do nothing */
	rlc_cntl = RREG32_SOC15(GC, 0, mmRLC_CNTL);
	return (REG_GET_FIELD(rlc_cntl, RLC_CNTL, RLC_ENABLE_F32)) ? true : false;
}