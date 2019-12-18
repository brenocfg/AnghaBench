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
struct TYPE_2__ {int kiq; int mec_ring7; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ doorbell_index; } ;

/* Variables and functions */
 scalar_t__ CHIP_TONGA ; 
 int /*<<< orphan*/  CP_PQ_STATUS ; 
 int /*<<< orphan*/  DOORBELL_ENABLE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_MEC_DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  mmCP_MEC_DOORBELL_RANGE_UPPER ; 

__attribute__((used)) static void gfx_v8_0_set_mec_doorbell_range(struct amdgpu_device *adev)
{
	if (adev->asic_type > CHIP_TONGA) {
		WREG32(mmCP_MEC_DOORBELL_RANGE_LOWER, adev->doorbell_index.kiq << 2);
		WREG32(mmCP_MEC_DOORBELL_RANGE_UPPER, adev->doorbell_index.mec_ring7 << 2);
	}
	/* enable doorbells */
	WREG32_FIELD(CP_PQ_STATUS, DOORBELL_ENABLE, 1);
}