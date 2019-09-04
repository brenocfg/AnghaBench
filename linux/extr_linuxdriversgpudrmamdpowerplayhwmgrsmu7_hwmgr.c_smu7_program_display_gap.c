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
typedef  int uint32_t ;
struct smu7_hwmgr {int frame_time_x2; scalar_t__ soft_regs_start; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; TYPE_1__* display_config; scalar_t__ adev; scalar_t__ backend; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ num_display; int vrefresh; int min_vblank_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_DISPLAY_GAP_CNTL ; 
 int /*<<< orphan*/  DISPLAY_GAP_IGNORE ; 
 int /*<<< orphan*/  DISPLAY_GAP_VBLANK_OR_WM ; 
 int /*<<< orphan*/  DISP_GAP ; 
 int PHM_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PreVBlankGap ; 
 int /*<<< orphan*/  SMU_SoftRegisters ; 
 int /*<<< orphan*/  VBlankTimeout ; 
 int amdgpu_asic_get_xclk (struct amdgpu_device*) ; 
 int cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cgs_write_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ ixCG_DISPLAY_GAP_CNTL ; 
 scalar_t__ ixCG_DISPLAY_GAP_CNTL2 ; 
 scalar_t__ smum_get_offsetof (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_program_display_gap(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	uint32_t display_gap = cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_DISPLAY_GAP_CNTL);
	uint32_t display_gap2;
	uint32_t pre_vbi_time_in_us;
	uint32_t frame_time_in_us;
	uint32_t ref_clock, refresh_rate;

	display_gap = PHM_SET_FIELD(display_gap, CG_DISPLAY_GAP_CNTL, DISP_GAP, (hwmgr->display_config->num_display > 0) ? DISPLAY_GAP_VBLANK_OR_WM : DISPLAY_GAP_IGNORE);
	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_DISPLAY_GAP_CNTL, display_gap);

	ref_clock =  amdgpu_asic_get_xclk((struct amdgpu_device *)hwmgr->adev);
	refresh_rate = hwmgr->display_config->vrefresh;

	if (0 == refresh_rate)
		refresh_rate = 60;

	frame_time_in_us = 1000000 / refresh_rate;

	pre_vbi_time_in_us = frame_time_in_us - 200 - hwmgr->display_config->min_vblank_time;

	data->frame_time_x2 = frame_time_in_us * 2 / 100;

	display_gap2 = pre_vbi_time_in_us * (ref_clock / 100);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_DISPLAY_GAP_CNTL2, display_gap2);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
			data->soft_regs_start + smum_get_offsetof(hwmgr,
							SMU_SoftRegisters,
							PreVBlankGap), 0x64);

	cgs_write_ind_register(hwmgr->device, CGS_IND_REG__SMC,
			data->soft_regs_start + smum_get_offsetof(hwmgr,
							SMU_SoftRegisters,
							VBlankTimeout),
					(frame_time_in_us - pre_vbi_time_in_us));

	return 0;
}