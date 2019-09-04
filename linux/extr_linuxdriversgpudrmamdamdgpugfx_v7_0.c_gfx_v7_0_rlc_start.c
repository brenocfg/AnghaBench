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
 int /*<<< orphan*/  RLC_CNTL__RLC_ENABLE_F32_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmRLC_CNTL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v7_0_rlc_start(struct amdgpu_device *adev)
{
	WREG32(mmRLC_CNTL, RLC_CNTL__RLC_ENABLE_F32_MASK);

	gfx_v7_0_enable_gui_idle_interrupt(adev, true);

	udelay(50);
}