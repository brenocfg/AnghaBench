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
struct TYPE_2__ {scalar_t__ num_crtc; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCE ; 
 int /*<<< orphan*/  VGA_HDP_CONTROL ; 
 int /*<<< orphan*/  VGA_MEMORY_DISABLE ; 
 int /*<<< orphan*/  VGA_RENDER_CONTROL ; 
 int /*<<< orphan*/  VGA_VSTATUS_CNTL ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gmc_v9_0_gart_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gmc_v9_0_init_golden_registers (struct amdgpu_device*) ; 

__attribute__((used)) static int gmc_v9_0_hw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* The sequence of these two function calls matters.*/
	gmc_v9_0_init_golden_registers(adev);

	if (adev->mode_info.num_crtc) {
		/* Lockout access through VGA aperture*/
		WREG32_FIELD15(DCE, 0, VGA_HDP_CONTROL, VGA_MEMORY_DISABLE, 1);

		/* disable VGA render */
		WREG32_FIELD15(DCE, 0, VGA_RENDER_CONTROL, VGA_VSTATUS_CNTL, 0);
	}

	r = gmc_v9_0_gart_enable(adev);

	return r;
}