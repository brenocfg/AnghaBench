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
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  RLC_CNTL ; 
 int /*<<< orphan*/  RLC_ENABLE_F32 ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v8_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v8_0_rlc_start(struct amdgpu_device *adev)
{
	WREG32_FIELD(RLC_CNTL, RLC_ENABLE_F32, 1);

	/* carrizo do enable cp interrupt after cp inited */
	if (!(adev->flags & AMD_IS_APU))
		gfx_v8_0_enable_gui_idle_interrupt(adev, true);

	udelay(50);
}