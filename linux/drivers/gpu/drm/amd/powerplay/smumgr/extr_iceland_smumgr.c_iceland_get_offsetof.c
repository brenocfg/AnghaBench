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
typedef  int uint32_t ;

/* Variables and functions */
#define  AverageGraphicsActivity 142 
#define  AverageMemoryActivity 141 
#define  DRAM_LOG_ADDR_H 140 
#define  DRAM_LOG_ADDR_L 139 
#define  DRAM_LOG_BUFF_SIZE 138 
#define  DRAM_LOG_PHY_ADDR_H 137 
#define  DRAM_LOG_PHY_ADDR_L 136 
#define  HandshakeDisables 135 
#define  LowSclkInterruptThreshold 134 
#define  PreVBlankGap 133 
 int /*<<< orphan*/  SMU71_Discrete_DpmTable ; 
 int /*<<< orphan*/  SMU71_SoftRegisters ; 
#define  SMU_Discrete_DpmTable 132 
#define  SMU_SoftRegisters 131 
#define  UcodeLoadStatus 130 
#define  VBlankTimeout 129 
#define  VoltageChangeTimeout 128 
 int offsetof (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 

__attribute__((used)) static uint32_t iceland_get_offsetof(uint32_t type, uint32_t member)
{
	switch (type) {
	case SMU_SoftRegisters:
		switch (member) {
		case HandshakeDisables:
			return offsetof(SMU71_SoftRegisters, HandshakeDisables);
		case VoltageChangeTimeout:
			return offsetof(SMU71_SoftRegisters, VoltageChangeTimeout);
		case AverageGraphicsActivity:
			return offsetof(SMU71_SoftRegisters, AverageGraphicsActivity);
		case AverageMemoryActivity:
			return offsetof(SMU71_SoftRegisters, AverageMemoryActivity);
		case PreVBlankGap:
			return offsetof(SMU71_SoftRegisters, PreVBlankGap);
		case VBlankTimeout:
			return offsetof(SMU71_SoftRegisters, VBlankTimeout);
		case UcodeLoadStatus:
			return offsetof(SMU71_SoftRegisters, UcodeLoadStatus);
		case DRAM_LOG_ADDR_H:
			return offsetof(SMU71_SoftRegisters, DRAM_LOG_ADDR_H);
		case DRAM_LOG_ADDR_L:
			return offsetof(SMU71_SoftRegisters, DRAM_LOG_ADDR_L);
		case DRAM_LOG_PHY_ADDR_H:
			return offsetof(SMU71_SoftRegisters, DRAM_LOG_PHY_ADDR_H);
		case DRAM_LOG_PHY_ADDR_L:
			return offsetof(SMU71_SoftRegisters, DRAM_LOG_PHY_ADDR_L);
		case DRAM_LOG_BUFF_SIZE:
			return offsetof(SMU71_SoftRegisters, DRAM_LOG_BUFF_SIZE);
		}
		break;
	case SMU_Discrete_DpmTable:
		switch (member) {
		case LowSclkInterruptThreshold:
			return offsetof(SMU71_Discrete_DpmTable, LowSclkInterruptThreshold);
		}
		break;
	}
	pr_warn("can't get the offset of type %x member %x\n", type, member);
	return 0;
}