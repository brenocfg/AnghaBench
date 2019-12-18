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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIF_MMSCH0_DOORBELL_RANGE ; 
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIF_MMSCH0_DOORBELL_RANGE ; 
 int /*<<< orphan*/  mmBIF_MMSCH1_DOORBELL_RANGE ; 

__attribute__((used)) static void nbio_v7_4_vcn_doorbell_range(struct amdgpu_device *adev, bool use_doorbell,
					 int doorbell_index, int instance)
{
	u32 reg;
	u32 doorbell_range;

	if (instance)
		reg = SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH1_DOORBELL_RANGE);
	else
		reg = SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH0_DOORBELL_RANGE);

	doorbell_range = RREG32(reg);

	if (use_doorbell) {
		doorbell_range = REG_SET_FIELD(doorbell_range,
					       BIF_MMSCH0_DOORBELL_RANGE, OFFSET,
					       doorbell_index);
		doorbell_range = REG_SET_FIELD(doorbell_range,
					       BIF_MMSCH0_DOORBELL_RANGE, SIZE, 8);
	} else
		doorbell_range = REG_SET_FIELD(doorbell_range,
					       BIF_MMSCH0_DOORBELL_RANGE, SIZE, 0);

	WREG32(reg, doorbell_range);
}