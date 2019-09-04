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
struct radeon_device {int dummy; } ;
struct evergreen_arb_registers {void* mc_arb_burst_time; void* mc_arb_rfsh_rate; void* mc_arb_dram_timing2; void* mc_arb_dram_timing; } ;
struct evergreen_power_info {struct evergreen_arb_registers bootup_arb_registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_ARB_BURST_TIME ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING2 ; 
 int /*<<< orphan*/  MC_ARB_RFSH_RATE ; 
 void* RREG32 (int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 

void btc_read_arb_registers(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct evergreen_arb_registers *arb_registers =
		&eg_pi->bootup_arb_registers;

	arb_registers->mc_arb_dram_timing = RREG32(MC_ARB_DRAM_TIMING);
	arb_registers->mc_arb_dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);
	arb_registers->mc_arb_rfsh_rate = RREG32(MC_ARB_RFSH_RATE);
	arb_registers->mc_arb_burst_time = RREG32(MC_ARB_BURST_TIME);
}