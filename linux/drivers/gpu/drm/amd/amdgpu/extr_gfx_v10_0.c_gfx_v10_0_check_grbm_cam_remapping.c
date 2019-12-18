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
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 scalar_t__ RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmVGT_ESGS_RING_SIZE ; 
 int /*<<< orphan*/  mmVGT_ESGS_RING_SIZE_UMD ; 

__attribute__((used)) static bool gfx_v10_0_check_grbm_cam_remapping(struct amdgpu_device *adev)
{
	uint32_t data, pattern = 0xDEADBEEF;

	/* check if mmVGT_ESGS_RING_SIZE_UMD
	 * has been remapped to mmVGT_ESGS_RING_SIZE */
	data = RREG32_SOC15(GC, 0, mmVGT_ESGS_RING_SIZE);

	WREG32_SOC15(GC, 0, mmVGT_ESGS_RING_SIZE, 0);

	WREG32_SOC15(GC, 0, mmVGT_ESGS_RING_SIZE_UMD, pattern);

	if (RREG32_SOC15(GC, 0, mmVGT_ESGS_RING_SIZE) == pattern) {
		WREG32_SOC15(GC, 0, mmVGT_ESGS_RING_SIZE_UMD, data);
		return true;
	} else {
		WREG32_SOC15(GC, 0, mmVGT_ESGS_RING_SIZE, data);
		return false;
	}
}