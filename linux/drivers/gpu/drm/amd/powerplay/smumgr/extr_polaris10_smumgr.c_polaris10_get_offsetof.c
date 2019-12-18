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
#define  AverageGraphicsActivity 144 
#define  AverageMemoryActivity 143 
#define  DRAM_LOG_ADDR_H 142 
#define  DRAM_LOG_ADDR_L 141 
#define  DRAM_LOG_BUFF_SIZE 140 
#define  DRAM_LOG_PHY_ADDR_H 139 
#define  DRAM_LOG_PHY_ADDR_L 138 
#define  HandshakeDisables 137 
#define  LowSclkInterruptThreshold 136 
#define  PreVBlankGap 135 
 int /*<<< orphan*/  SMU74_Discrete_DpmTable ; 
 int /*<<< orphan*/  SMU74_SoftRegisters ; 
#define  SMU_Discrete_DpmTable 134 
#define  SMU_SoftRegisters 133 
#define  UcodeLoadStatus 132 
#define  UvdBootLevel 131 
#define  VBlankTimeout 130 
#define  VceBootLevel 129 
#define  VoltageChangeTimeout 128 
 int offsetof (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 

__attribute__((used)) static uint32_t polaris10_get_offsetof(uint32_t type, uint32_t member)
{
	switch (type) {
	case SMU_SoftRegisters:
		switch (member) {
		case HandshakeDisables:
			return offsetof(SMU74_SoftRegisters, HandshakeDisables);
		case VoltageChangeTimeout:
			return offsetof(SMU74_SoftRegisters, VoltageChangeTimeout);
		case AverageGraphicsActivity:
			return offsetof(SMU74_SoftRegisters, AverageGraphicsActivity);
		case AverageMemoryActivity:
			return offsetof(SMU74_SoftRegisters, AverageMemoryActivity);
		case PreVBlankGap:
			return offsetof(SMU74_SoftRegisters, PreVBlankGap);
		case VBlankTimeout:
			return offsetof(SMU74_SoftRegisters, VBlankTimeout);
		case UcodeLoadStatus:
			return offsetof(SMU74_SoftRegisters, UcodeLoadStatus);
		case DRAM_LOG_ADDR_H:
			return offsetof(SMU74_SoftRegisters, DRAM_LOG_ADDR_H);
		case DRAM_LOG_ADDR_L:
			return offsetof(SMU74_SoftRegisters, DRAM_LOG_ADDR_L);
		case DRAM_LOG_PHY_ADDR_H:
			return offsetof(SMU74_SoftRegisters, DRAM_LOG_PHY_ADDR_H);
		case DRAM_LOG_PHY_ADDR_L:
			return offsetof(SMU74_SoftRegisters, DRAM_LOG_PHY_ADDR_L);
		case DRAM_LOG_BUFF_SIZE:
			return offsetof(SMU74_SoftRegisters, DRAM_LOG_BUFF_SIZE);
		}
		break;
	case SMU_Discrete_DpmTable:
		switch (member) {
		case UvdBootLevel:
			return offsetof(SMU74_Discrete_DpmTable, UvdBootLevel);
		case VceBootLevel:
			return offsetof(SMU74_Discrete_DpmTable, VceBootLevel);
		case LowSclkInterruptThreshold:
			return offsetof(SMU74_Discrete_DpmTable, LowSclkInterruptThreshold);
		}
		break;
	}
	pr_warn("can't get the offset of type %x member %x\n", type, member);
	return 0;
}