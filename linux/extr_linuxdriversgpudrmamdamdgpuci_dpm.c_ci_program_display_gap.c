#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int new_active_crtc_count; } ;
struct TYPE_8__ {TYPE_3__ dpm; } ;
struct TYPE_5__ {int reference_freq; } ;
struct TYPE_6__ {TYPE_1__ spll; } ;
struct amdgpu_device {TYPE_4__ pm; TYPE_2__ clock; } ;

/* Variables and functions */
 int AMDGPU_PM_DISPLAY_GAP_IGNORE ; 
 int AMDGPU_PM_DISPLAY_GAP_VBLANK_OR_WM ; 
 int CG_DISPLAY_GAP_CNTL__DISP_GAP_MASK ; 
 int CG_DISPLAY_GAP_CNTL__DISP_GAP__SHIFT ; 
 int /*<<< orphan*/  PreVBlankGap ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU7_SoftRegisters ; 
 int /*<<< orphan*/  VBlankTimeout ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int amdgpu_dpm_get_vblank_time (struct amdgpu_device*) ; 
 int amdgpu_dpm_get_vrefresh (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_notify_smc_display_change (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_write_smc_soft_register (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixCG_DISPLAY_GAP_CNTL ; 
 int /*<<< orphan*/  ixCG_DISPLAY_GAP_CNTL2 ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ci_program_display_gap(struct amdgpu_device *adev)
{
	u32 tmp = RREG32_SMC(ixCG_DISPLAY_GAP_CNTL);
	u32 pre_vbi_time_in_us;
	u32 frame_time_in_us;
	u32 ref_clock = adev->clock.spll.reference_freq;
	u32 refresh_rate = amdgpu_dpm_get_vrefresh(adev);
	u32 vblank_time = amdgpu_dpm_get_vblank_time(adev);

	tmp &= ~CG_DISPLAY_GAP_CNTL__DISP_GAP_MASK;
	if (adev->pm.dpm.new_active_crtc_count > 0)
		tmp |= (AMDGPU_PM_DISPLAY_GAP_VBLANK_OR_WM << CG_DISPLAY_GAP_CNTL__DISP_GAP__SHIFT);
	else
		tmp |= (AMDGPU_PM_DISPLAY_GAP_IGNORE << CG_DISPLAY_GAP_CNTL__DISP_GAP__SHIFT);
	WREG32_SMC(ixCG_DISPLAY_GAP_CNTL, tmp);

	if (refresh_rate == 0)
		refresh_rate = 60;
	if (vblank_time == 0xffffffff)
		vblank_time = 500;
	frame_time_in_us = 1000000 / refresh_rate;
	pre_vbi_time_in_us =
		frame_time_in_us - 200 - vblank_time;
	tmp = pre_vbi_time_in_us * (ref_clock / 100);

	WREG32_SMC(ixCG_DISPLAY_GAP_CNTL2, tmp);
	ci_write_smc_soft_register(adev, offsetof(SMU7_SoftRegisters, PreVBlankGap), 0x64);
	ci_write_smc_soft_register(adev, offsetof(SMU7_SoftRegisters, VBlankTimeout), (frame_time_in_us - pre_vbi_time_in_us));


	ci_notify_smc_display_change(adev, (adev->pm.dpm.new_active_crtc_count == 1));

}