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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_ring {int doorbell_index; scalar_t__ use_doorbell; } ;
struct TYPE_2__ {int gfx_ring0; } ;
struct amdgpu_device {scalar_t__ asic_type; int flags; TYPE_1__ doorbell_index; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 scalar_t__ CHIP_TOPAZ ; 
 int /*<<< orphan*/  CP_RB_DOORBELL_CONTROL ; 
 int /*<<< orphan*/  CP_RB_DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  CP_RB_DOORBELL_RANGE_UPPER__DOORBELL_RANGE_UPPER_MASK ; 
 int /*<<< orphan*/  DOORBELL_EN ; 
 int /*<<< orphan*/  DOORBELL_HIT ; 
 int /*<<< orphan*/  DOORBELL_OFFSET ; 
 int /*<<< orphan*/  DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_RB_DOORBELL_CONTROL ; 
 int /*<<< orphan*/  mmCP_RB_DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  mmCP_RB_DOORBELL_RANGE_UPPER ; 

__attribute__((used)) static void gfx_v8_0_set_cpg_door_bell(struct amdgpu_device *adev, struct amdgpu_ring *ring)
{
	u32 tmp;
	/* no gfx doorbells on iceland */
	if (adev->asic_type == CHIP_TOPAZ)
		return;

	tmp = RREG32(mmCP_RB_DOORBELL_CONTROL);

	if (ring->use_doorbell) {
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
				DOORBELL_OFFSET, ring->doorbell_index);
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
						DOORBELL_HIT, 0);
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
					    DOORBELL_EN, 1);
	} else {
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL, DOORBELL_EN, 0);
	}

	WREG32(mmCP_RB_DOORBELL_CONTROL, tmp);

	if (adev->flags & AMD_IS_APU)
		return;

	tmp = REG_SET_FIELD(0, CP_RB_DOORBELL_RANGE_LOWER,
					DOORBELL_RANGE_LOWER,
					adev->doorbell_index.gfx_ring0);
	WREG32(mmCP_RB_DOORBELL_RANGE_LOWER, tmp);

	WREG32(mmCP_RB_DOORBELL_RANGE_UPPER,
		CP_RB_DOORBELL_RANGE_UPPER__DOORBELL_RANGE_UPPER_MASK);
}