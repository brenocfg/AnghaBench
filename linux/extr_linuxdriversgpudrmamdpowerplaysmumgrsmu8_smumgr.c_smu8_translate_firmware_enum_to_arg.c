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
typedef  int /*<<< orphan*/  uint8_t ;
struct pp_hwmgr {int /*<<< orphan*/  chip_id; } ;
typedef  enum smu8_scratch_entry { ____Placeholder_smu8_scratch_entry } smu8_scratch_entry ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_STONEY ; 
#define  SMU8_SCRATCH_ENTRY_DATA_ID_IH_REGISTERS 149 
#define  SMU8_SCRATCH_ENTRY_DATA_ID_NONGFX_REINIT 148 
#define  SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_HALT 147 
#define  SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_RING_REGS 146 
#define  SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_START 145 
#define  SMU8_SCRATCH_ENTRY_DATA_ID_SYS_CLOCKGATING 144 
#define  SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE 143 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE 142 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME 141 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1 140 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2 139 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP 138 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_ERAM 137 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_IRAM 136 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_GMCON_RENG 135 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING 134 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G 133 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH 132 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM 131 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM 130 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0 129 
#define  SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1 128 
 int /*<<< orphan*/  TASK_ARG_INIT_CLK_TABLE ; 
 int /*<<< orphan*/  TASK_ARG_INIT_MM_PWR_LOG ; 
 int /*<<< orphan*/  TASK_ARG_REG_MMIO ; 
 int /*<<< orphan*/  UCODE_ID_CP_CE ; 
 int /*<<< orphan*/  UCODE_ID_CP_ME ; 
 int /*<<< orphan*/  UCODE_ID_CP_MEC_JT1 ; 
 int /*<<< orphan*/  UCODE_ID_CP_MEC_JT2 ; 
 int /*<<< orphan*/  UCODE_ID_CP_PFP ; 
 int /*<<< orphan*/  UCODE_ID_DMCU_ERAM ; 
 int /*<<< orphan*/  UCODE_ID_DMCU_IRAM ; 
 int /*<<< orphan*/  UCODE_ID_GMCON_RENG ; 
 int /*<<< orphan*/  UCODE_ID_RLC_G ; 
 int /*<<< orphan*/  UCODE_ID_RLC_SCRATCH ; 
 int /*<<< orphan*/  UCODE_ID_RLC_SRM_ARAM ; 
 int /*<<< orphan*/  UCODE_ID_RLC_SRM_DRAM ; 
 int /*<<< orphan*/  UCODE_ID_SDMA0 ; 
 int /*<<< orphan*/  UCODE_ID_SDMA1 ; 

__attribute__((used)) static uint8_t smu8_translate_firmware_enum_to_arg(struct pp_hwmgr *hwmgr,
			enum smu8_scratch_entry firmware_enum)
{
	uint8_t ret = 0;

	switch (firmware_enum) {
	case SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0:
		ret = UCODE_ID_SDMA0;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1:
		if (hwmgr->chip_id == CHIP_STONEY)
			ret = UCODE_ID_SDMA0;
		else
			ret = UCODE_ID_SDMA1;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE:
		ret = UCODE_ID_CP_CE;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP:
		ret = UCODE_ID_CP_PFP;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME:
		ret = UCODE_ID_CP_ME;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1:
		ret = UCODE_ID_CP_MEC_JT1;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2:
		if (hwmgr->chip_id == CHIP_STONEY)
			ret = UCODE_ID_CP_MEC_JT1;
		else
			ret = UCODE_ID_CP_MEC_JT2;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_GMCON_RENG:
		ret = UCODE_ID_GMCON_RENG;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G:
		ret = UCODE_ID_RLC_G;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH:
		ret = UCODE_ID_RLC_SCRATCH;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM:
		ret = UCODE_ID_RLC_SRM_ARAM;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM:
		ret = UCODE_ID_RLC_SRM_DRAM;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_ERAM:
		ret = UCODE_ID_DMCU_ERAM;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_IRAM:
		ret = UCODE_ID_DMCU_IRAM;
		break;
	case SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING:
		ret = TASK_ARG_INIT_MM_PWR_LOG;
		break;
	case SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_HALT:
	case SMU8_SCRATCH_ENTRY_DATA_ID_SYS_CLOCKGATING:
	case SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_RING_REGS:
	case SMU8_SCRATCH_ENTRY_DATA_ID_NONGFX_REINIT:
	case SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_START:
	case SMU8_SCRATCH_ENTRY_DATA_ID_IH_REGISTERS:
		ret = TASK_ARG_REG_MMIO;
		break;
	case SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE:
		ret = TASK_ARG_INIT_CLK_TABLE;
		break;
	}

	return ret;
}