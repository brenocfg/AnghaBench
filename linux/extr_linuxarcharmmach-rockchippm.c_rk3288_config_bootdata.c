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
 int SZ_4K ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_resume ; 
 int rk3288_bootram_phy ; 
 int /*<<< orphan*/  rk3288_l2_config () ; 
 int /*<<< orphan*/  rkpm_bootdata_cpu_code ; 
 int rkpm_bootdata_cpusp ; 
 int /*<<< orphan*/  rkpm_bootdata_l2ctlr ; 
 int rkpm_bootdata_l2ctlr_f ; 

__attribute__((used)) static void rk3288_config_bootdata(void)
{
	rkpm_bootdata_cpusp = rk3288_bootram_phy + (SZ_4K - 8);
	rkpm_bootdata_cpu_code = __pa_symbol(cpu_resume);

	rkpm_bootdata_l2ctlr_f  = 1;
	rkpm_bootdata_l2ctlr = rk3288_l2_config();
}