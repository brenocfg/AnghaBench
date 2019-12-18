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

/* Variables and functions */
#define  ARM_SMMU_GR0_sACR 133 
#define  ARM_SMMU_GR0_sCR0 132 
#define  ARM_SMMU_GR0_sGFSR 131 
#define  ARM_SMMU_GR0_sGFSYNR0 130 
#define  ARM_SMMU_GR0_sGFSYNR1 129 
#define  ARM_SMMU_GR0_sGFSYNR2 128 

__attribute__((used)) static int arm_smmu_gr0_ns(int offset)
{
	switch(offset) {
	case ARM_SMMU_GR0_sCR0:
	case ARM_SMMU_GR0_sACR:
	case ARM_SMMU_GR0_sGFSR:
	case ARM_SMMU_GR0_sGFSYNR0:
	case ARM_SMMU_GR0_sGFSYNR1:
	case ARM_SMMU_GR0_sGFSYNR2:
		return offset + 0x400;
	default:
		return offset;
	}
}