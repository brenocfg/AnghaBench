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
struct TYPE_2__ {int /*<<< orphan*/  rlc_fw_version; } ;
struct amdgpu_device {int flags; TYPE_1__ gfx; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  DRM_INFO (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  RLC_CNTL ; 
 int /*<<< orphan*/  RLC_ENABLE_F32 ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmRLC_GPM_GENERAL_12 ; 
 int /*<<< orphan*/  mmRLC_GPM_GENERAL_6 ; 
 int /*<<< orphan*/  mmRLC_GPM_TIMER_INT_3 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v9_0_rlc_start(struct amdgpu_device *adev)
{
#ifdef AMDGPU_RLC_DEBUG_RETRY
	u32 rlc_ucode_ver;
#endif

	WREG32_FIELD15(GC, 0, RLC_CNTL, RLC_ENABLE_F32, 1);
	udelay(50);

	/* carrizo do enable cp interrupt after cp inited */
	if (!(adev->flags & AMD_IS_APU)) {
		gfx_v9_0_enable_gui_idle_interrupt(adev, true);
		udelay(50);
	}

#ifdef AMDGPU_RLC_DEBUG_RETRY
	/* RLC_GPM_GENERAL_6 : RLC Ucode version */
	rlc_ucode_ver = RREG32_SOC15(GC, 0, mmRLC_GPM_GENERAL_6);
	if(rlc_ucode_ver == 0x108) {
		DRM_INFO("Using rlc debug ucode. mmRLC_GPM_GENERAL_6 ==0x08%x / fw_ver == %i \n",
				rlc_ucode_ver, adev->gfx.rlc_fw_version);
		/* RLC_GPM_TIMER_INT_3 : Timer interval in RefCLK cycles,
		 * default is 0x9C4 to create a 100us interval */
		WREG32_SOC15(GC, 0, mmRLC_GPM_TIMER_INT_3, 0x9C4);
		/* RLC_GPM_GENERAL_12 : Minimum gap between wptr and rptr
		 * to disable the page fault retry interrupts, default is
		 * 0x100 (256) */
		WREG32_SOC15(GC, 0, mmRLC_GPM_GENERAL_12, 0x100);
	}
#endif
}