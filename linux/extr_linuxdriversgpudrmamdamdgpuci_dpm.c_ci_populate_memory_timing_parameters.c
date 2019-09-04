#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ McArbBurstTime; void* McArbDramTiming2; void* McArbDramTiming; } ;
typedef  TYPE_1__ SMU7_Discrete_MCArbDramTimingTableEntry ;

/* Variables and functions */
 int MC_ARB_BURST_TIME__STATE0_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_set_engine_dram_timings (struct amdgpu_device*,int,int) ; 
 int /*<<< orphan*/  ci_register_patching_mc_arb (struct amdgpu_device*,int,int,int*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  mmMC_ARB_BURST_TIME ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING ; 
 int /*<<< orphan*/  mmMC_ARB_DRAM_TIMING2 ; 

__attribute__((used)) static int ci_populate_memory_timing_parameters(struct amdgpu_device *adev,
						u32 sclk,
						u32 mclk,
						SMU7_Discrete_MCArbDramTimingTableEntry *arb_regs)
{
	u32 dram_timing;
	u32 dram_timing2;
	u32 burst_time;

	amdgpu_atombios_set_engine_dram_timings(adev, sclk, mclk);

	dram_timing  = RREG32(mmMC_ARB_DRAM_TIMING);
	dram_timing2 = RREG32(mmMC_ARB_DRAM_TIMING2);
	burst_time = RREG32(mmMC_ARB_BURST_TIME) & MC_ARB_BURST_TIME__STATE0_MASK;

	ci_register_patching_mc_arb(adev, sclk, mclk, &dram_timing2);

	arb_regs->McArbDramTiming  = cpu_to_be32(dram_timing);
	arb_regs->McArbDramTiming2 = cpu_to_be32(dram_timing2);
	arb_regs->McArbBurstTime = (u8)burst_time;

	return 0;
}