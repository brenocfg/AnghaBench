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
typedef  int u32 ;
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIF_SDMA0_DOORBELL_RANGE ; 
 scalar_t__ CHIP_VEGA20 ; 
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  OFFSET ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  SIZE ; 
 int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  mmBIF_SDMA0_DOORBELL_RANGE ; 
 int /*<<< orphan*/  mmBIF_SDMA1_DOORBELL_RANGE ; 

__attribute__((used)) static void nbio_v7_0_sdma_doorbell_range(struct amdgpu_device *adev, int instance,
					  bool use_doorbell, int doorbell_index)
{
	u32 reg = instance == 0 ? SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA0_DOORBELL_RANGE) :
			SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA1_DOORBELL_RANGE);

	u32 doorbell_range = RREG32(reg);
	u32 range = 2;

	if (adev->asic_type == CHIP_VEGA20)
		range = 8;

	if (use_doorbell) {
		doorbell_range = REG_SET_FIELD(doorbell_range, BIF_SDMA0_DOORBELL_RANGE, OFFSET, doorbell_index);
		doorbell_range = REG_SET_FIELD(doorbell_range, BIF_SDMA0_DOORBELL_RANGE, SIZE, range);
	} else
		doorbell_range = REG_SET_FIELD(doorbell_range, BIF_SDMA0_DOORBELL_RANGE, SIZE, 0);

	WREG32(reg, doorbell_range);
}