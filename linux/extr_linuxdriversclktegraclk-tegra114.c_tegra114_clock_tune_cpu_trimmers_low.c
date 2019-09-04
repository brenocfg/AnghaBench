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

/* Variables and functions */
 int CPU_FINETRIM_1_FCPU_1 ; 
 int CPU_FINETRIM_1_FCPU_2 ; 
 int CPU_FINETRIM_1_FCPU_3 ; 
 int CPU_FINETRIM_1_FCPU_4 ; 
 int CPU_FINETRIM_1_FCPU_5 ; 
 int CPU_FINETRIM_1_FCPU_6 ; 
 scalar_t__ CPU_FINETRIM_SELECT ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  tegra114_car_barrier () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void tegra114_clock_tune_cpu_trimmers_low(void)
{
	u32 select = 0;

	/*
	 * Use software-specified rise->rise & fall->fall clock
	 * propagation delays (from
	 * tegra114_clock_tune_cpu_trimmers_init()
	 */
	select |= (CPU_FINETRIM_1_FCPU_1 | CPU_FINETRIM_1_FCPU_2 |
		   CPU_FINETRIM_1_FCPU_3 | CPU_FINETRIM_1_FCPU_4 |
		   CPU_FINETRIM_1_FCPU_5 | CPU_FINETRIM_1_FCPU_6);
	writel_relaxed(select, clk_base + CPU_FINETRIM_SELECT);

	tegra114_car_barrier();
}