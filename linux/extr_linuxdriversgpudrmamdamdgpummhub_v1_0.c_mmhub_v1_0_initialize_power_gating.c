#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMHUB ; 
 int PCTL0_DATA_LEN ; 
 int /*<<< orphan*/  PCTL0_MISC__RENG_MEM_LS_ENABLE_MASK ; 
 int /*<<< orphan*/  PCTL0_RENG_EXECUTE ; 
 int /*<<< orphan*/  PCTL0_RENG_EXEC_END_PTR ; 
 int PCTL1_DATA_LEN ; 
 int /*<<< orphan*/  PCTL1_MISC__RENG_MEM_LS_ENABLE_MASK ; 
 int /*<<< orphan*/  PCTL1_RENG_EXECUTE ; 
 int /*<<< orphan*/  PCTL1_RENG_EXEC_END_PTR ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RENG_EXECUTE_END_PTR ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmPCTL0_MISC ; 
 int /*<<< orphan*/  mmPCTL0_RENG_EXECUTE ; 
 int /*<<< orphan*/  mmPCTL0_RENG_RAM_DATA ; 
 int /*<<< orphan*/  mmPCTL0_RENG_RAM_INDEX ; 
 int /*<<< orphan*/  mmPCTL1_MISC ; 
 int /*<<< orphan*/  mmPCTL1_RENG_EXECUTE ; 
 int /*<<< orphan*/  mmPCTL1_RENG_RAM_DATA ; 
 int /*<<< orphan*/  mmPCTL1_RENG_RAM_INDEX ; 
 int /*<<< orphan*/  mmhub_v1_0_power_gating_write_save_ranges (struct amdgpu_device*) ; 
 TYPE_2__* pctl0_data ; 
 TYPE_1__* pctl1_data ; 

void mmhub_v1_0_initialize_power_gating(struct amdgpu_device *adev)
{
	uint32_t pctl0_misc = 0;
	uint32_t pctl0_reng_execute = 0;
	uint32_t pctl1_misc = 0;
	uint32_t pctl1_reng_execute = 0;
	int i = 0;

	if (amdgpu_sriov_vf(adev))
		return;

	/****************** pctl0 **********************/
	pctl0_misc = RREG32_SOC15(MMHUB, 0, mmPCTL0_MISC);
	pctl0_reng_execute = RREG32_SOC15(MMHUB, 0, mmPCTL0_RENG_EXECUTE);

	/* Light sleep must be disabled before writing to pctl0 registers */
	pctl0_misc &= ~PCTL0_MISC__RENG_MEM_LS_ENABLE_MASK;
	WREG32_SOC15(MMHUB, 0, mmPCTL0_MISC, pctl0_misc);

	/* Write data used to access ram of register engine */
	for (i = 0; i < PCTL0_DATA_LEN; i++) {
                WREG32_SOC15(MMHUB, 0, mmPCTL0_RENG_RAM_INDEX,
			pctl0_data[i].index);
                WREG32_SOC15(MMHUB, 0, mmPCTL0_RENG_RAM_DATA,
			pctl0_data[i].data);
        }

	/* Re-enable light sleep */
	pctl0_misc |= PCTL0_MISC__RENG_MEM_LS_ENABLE_MASK;
	WREG32_SOC15(MMHUB, 0, mmPCTL0_MISC, pctl0_misc);

	/****************** pctl1 **********************/
	pctl1_misc = RREG32_SOC15(MMHUB, 0, mmPCTL1_MISC);
	pctl1_reng_execute = RREG32_SOC15(MMHUB, 0, mmPCTL1_RENG_EXECUTE);

	/* Light sleep must be disabled before writing to pctl1 registers */
	pctl1_misc &= ~PCTL1_MISC__RENG_MEM_LS_ENABLE_MASK;
	WREG32_SOC15(MMHUB, 0, mmPCTL1_MISC, pctl1_misc);

	/* Write data used to access ram of register engine */
	for (i = 0; i < PCTL1_DATA_LEN; i++) {
                WREG32_SOC15(MMHUB, 0, mmPCTL1_RENG_RAM_INDEX,
			pctl1_data[i].index);
                WREG32_SOC15(MMHUB, 0, mmPCTL1_RENG_RAM_DATA,
			pctl1_data[i].data);
        }

	/* Re-enable light sleep */
	pctl1_misc |= PCTL1_MISC__RENG_MEM_LS_ENABLE_MASK;
	WREG32_SOC15(MMHUB, 0, mmPCTL1_MISC, pctl1_misc);

	mmhub_v1_0_power_gating_write_save_ranges(adev);

	/* Set the reng execute end ptr for pctl0 */
	pctl0_reng_execute = REG_SET_FIELD(pctl0_reng_execute,
					PCTL0_RENG_EXECUTE,
					RENG_EXECUTE_END_PTR,
					PCTL0_RENG_EXEC_END_PTR);
	WREG32_SOC15(MMHUB, 0, mmPCTL0_RENG_EXECUTE, pctl0_reng_execute);

	/* Set the reng execute end ptr for pctl1 */
	pctl1_reng_execute = REG_SET_FIELD(pctl1_reng_execute,
					PCTL1_RENG_EXECUTE,
					RENG_EXECUTE_END_PTR,
					PCTL1_RENG_EXEC_END_PTR);
	WREG32_SOC15(MMHUB, 0, mmPCTL1_RENG_EXECUTE, pctl1_reng_execute);
}