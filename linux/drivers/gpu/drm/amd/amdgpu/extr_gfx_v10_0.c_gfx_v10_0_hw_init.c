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
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {int /*<<< orphan*/  smu; TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  amdgpu_emu_mode ; 
 int /*<<< orphan*/  gfx_v10_0_check_grbm_cam_remapping (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_constants_init (struct amdgpu_device*) ; 
 int gfx_v10_0_cp_resume (struct amdgpu_device*) ; 
 int gfx_v10_0_csb_vram_pin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_init_golden_registers (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_resume (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_setup_grbm_cam_remapping (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_tcp_harvest (struct amdgpu_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_check_fw_status (int /*<<< orphan*/ *) ; 
 int smu_load_microcode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfx_v10_0_hw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = gfx_v10_0_csb_vram_pin(adev);
	if (r)
		return r;

	if (!amdgpu_emu_mode)
		gfx_v10_0_init_golden_registers(adev);

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT) {
		/**
		 * For gfx 10, rlc firmware loading relies on smu firmware is
		 * loaded firstly, so in direct type, it has to load smc ucode
		 * here before rlc.
		 */
		r = smu_load_microcode(&adev->smu);
		if (r)
			return r;

		r = smu_check_fw_status(&adev->smu);
		if (r) {
			pr_err("SMC firmware status is not correct\n");
			return r;
		}
	}

	/* if GRBM CAM not remapped, set up the remapping */
	if (!gfx_v10_0_check_grbm_cam_remapping(adev))
		gfx_v10_0_setup_grbm_cam_remapping(adev);

	gfx_v10_0_constants_init(adev);

	r = gfx_v10_0_rlc_resume(adev);
	if (r)
		return r;

	/*
	 * init golden registers and rlc resume may override some registers,
	 * reconfig them here
	 */
	gfx_v10_0_tcp_harvest(adev);

	r = gfx_v10_0_cp_resume(adev);
	if (r)
		return r;

	return r;
}