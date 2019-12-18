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
typedef  unsigned int u32 ;
struct TYPE_2__ {int num_instances; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_CTXSW_ENABLE ; 
 unsigned int REG_SET_FIELD (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0_CNTL ; 
 unsigned int SDMA0_PHASE0_QUANTUM__UNIT_MASK ; 
 unsigned int SDMA0_PHASE0_QUANTUM__UNIT__SHIFT ; 
 unsigned int SDMA0_PHASE0_QUANTUM__VALUE_MASK ; 
 unsigned int SDMA0_PHASE0_QUANTUM__VALUE__SHIFT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,unsigned int) ; 
 int amdgpu_sdma_phase_quantum ; 
 int /*<<< orphan*/  mmSDMA0_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_PHASE0_QUANTUM ; 
 int /*<<< orphan*/  mmSDMA0_PHASE1_QUANTUM ; 
 int /*<<< orphan*/  mmSDMA0_PHASE2_QUANTUM ; 
 int /*<<< orphan*/  sdma_v5_0_get_reg_offset (struct amdgpu_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdma_v5_0_ctx_switch_enable(struct amdgpu_device *adev, bool enable)
{
	u32 f32_cntl, phase_quantum = 0;
	int i;

	if (amdgpu_sdma_phase_quantum) {
		unsigned value = amdgpu_sdma_phase_quantum;
		unsigned unit = 0;

		while (value > (SDMA0_PHASE0_QUANTUM__VALUE_MASK >>
				SDMA0_PHASE0_QUANTUM__VALUE__SHIFT)) {
			value = (value + 1) >> 1;
			unit++;
		}
		if (unit > (SDMA0_PHASE0_QUANTUM__UNIT_MASK >>
			    SDMA0_PHASE0_QUANTUM__UNIT__SHIFT)) {
			value = (SDMA0_PHASE0_QUANTUM__VALUE_MASK >>
				 SDMA0_PHASE0_QUANTUM__VALUE__SHIFT);
			unit = (SDMA0_PHASE0_QUANTUM__UNIT_MASK >>
				SDMA0_PHASE0_QUANTUM__UNIT__SHIFT);
			WARN_ONCE(1,
			"clamping sdma_phase_quantum to %uK clock cycles\n",
				  value << unit);
		}
		phase_quantum =
			value << SDMA0_PHASE0_QUANTUM__VALUE__SHIFT |
			unit  << SDMA0_PHASE0_QUANTUM__UNIT__SHIFT;
	}

	for (i = 0; i < adev->sdma.num_instances; i++) {
		f32_cntl = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_CNTL));
		f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_CNTL,
				AUTO_CTXSW_ENABLE, enable ? 1 : 0);
		if (enable && amdgpu_sdma_phase_quantum) {
			WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_PHASE0_QUANTUM),
			       phase_quantum);
			WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_PHASE1_QUANTUM),
			       phase_quantum);
			WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_PHASE2_QUANTUM),
			       phase_quantum);
		}
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_CNTL), f32_cntl);
	}

}