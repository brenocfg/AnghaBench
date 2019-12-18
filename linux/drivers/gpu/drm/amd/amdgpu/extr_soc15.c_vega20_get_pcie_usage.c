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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  COUNTER0_UPPER ; 
 int /*<<< orphan*/  COUNTER1_UPPER ; 
 int /*<<< orphan*/  EVENT0_SEL ; 
 int /*<<< orphan*/  EVENT1_SEL ; 
 int /*<<< orphan*/  PCIE_PERF_CNTL_TXCLK3 ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  smnPCIE_PERF_CNTL_TXCLK3 ; 
 int /*<<< orphan*/  smnPCIE_PERF_COUNT0_TXCLK3 ; 
 int /*<<< orphan*/  smnPCIE_PERF_COUNT1_TXCLK3 ; 
 int /*<<< orphan*/  smnPCIE_PERF_COUNT_CNTL ; 

__attribute__((used)) static void vega20_get_pcie_usage(struct amdgpu_device *adev, uint64_t *count0,
				 uint64_t *count1)
{
	uint32_t perfctr = 0;
	uint64_t cnt0_of, cnt1_of;
	int tmp;

	/* This reports 0 on APUs, so return to avoid writing/reading registers
	 * that may or may not be different from their GPU counterparts
	 */
	if (adev->flags & AMD_IS_APU)
		return;

	/* Set the 2 events that we wish to watch, defined above */
	/* Reg 40 is # received msgs */
	/* Reg 108 is # of posted requests sent on VG20 */
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK3,
				EVENT0_SEL, 40);
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK3,
				EVENT1_SEL, 108);

	/* Write to enable desired perf counters */
	WREG32_PCIE(smnPCIE_PERF_CNTL_TXCLK3, perfctr);
	/* Zero out and enable the perf counters
	 * Write 0x5:
	 * Bit 0 = Start all counters(1)
	 * Bit 2 = Global counter reset enable(1)
	 */
	WREG32_PCIE(smnPCIE_PERF_COUNT_CNTL, 0x00000005);

	msleep(1000);

	/* Load the shadow and disable the perf counters
	 * Write 0x2:
	 * Bit 0 = Stop counters(0)
	 * Bit 1 = Load the shadow counters(1)
	 */
	WREG32_PCIE(smnPCIE_PERF_COUNT_CNTL, 0x00000002);

	/* Read register values to get any >32bit overflow */
	tmp = RREG32_PCIE(smnPCIE_PERF_CNTL_TXCLK3);
	cnt0_of = REG_GET_FIELD(tmp, PCIE_PERF_CNTL_TXCLK3, COUNTER0_UPPER);
	cnt1_of = REG_GET_FIELD(tmp, PCIE_PERF_CNTL_TXCLK3, COUNTER1_UPPER);

	/* Get the values and add the overflow */
	*count0 = RREG32_PCIE(smnPCIE_PERF_COUNT0_TXCLK3) | (cnt0_of << 32);
	*count1 = RREG32_PCIE(smnPCIE_PERF_COUNT1_TXCLK3) | (cnt1_of << 32);
}