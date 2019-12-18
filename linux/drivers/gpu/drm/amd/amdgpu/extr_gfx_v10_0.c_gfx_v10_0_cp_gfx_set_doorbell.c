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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_ring {int doorbell_index; scalar_t__ use_doorbell; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_RB_DOORBELL_CONTROL ; 
 int /*<<< orphan*/  CP_RB_DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  CP_RB_DOORBELL_RANGE_UPPER__DOORBELL_RANGE_UPPER_MASK ; 
 int /*<<< orphan*/  DOORBELL_EN ; 
 int /*<<< orphan*/  DOORBELL_OFFSET ; 
 int /*<<< orphan*/  DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_RB_DOORBELL_CONTROL ; 
 int /*<<< orphan*/  mmCP_RB_DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  mmCP_RB_DOORBELL_RANGE_UPPER ; 

__attribute__((used)) static void gfx_v10_0_cp_gfx_set_doorbell(struct amdgpu_device *adev,
					  struct amdgpu_ring *ring)
{
	u32 tmp;

	tmp = RREG32_SOC15(GC, 0, mmCP_RB_DOORBELL_CONTROL);
	if (ring->use_doorbell) {
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
				    DOORBELL_OFFSET, ring->doorbell_index);
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
				    DOORBELL_EN, 1);
	} else {
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
				    DOORBELL_EN, 0);
	}
	WREG32_SOC15(GC, 0, mmCP_RB_DOORBELL_CONTROL, tmp);
	tmp = REG_SET_FIELD(0, CP_RB_DOORBELL_RANGE_LOWER,
			    DOORBELL_RANGE_LOWER, ring->doorbell_index);
	WREG32_SOC15(GC, 0, mmCP_RB_DOORBELL_RANGE_LOWER, tmp);

	WREG32_SOC15(GC, 0, mmCP_RB_DOORBELL_RANGE_UPPER,
		     CP_RB_DOORBELL_RANGE_UPPER__DOORBELL_RANGE_UPPER_MASK);
}