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
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  arc_cache_init () ; 
 int /*<<< orphan*/  arc_chk_core_config () ; 
 int /*<<< orphan*/  arc_cpu_mumbojumbo (int,char*,int) ; 
 int /*<<< orphan*/  arc_extn_mumbojumbo (int,char*,int) ; 
 int /*<<< orphan*/  arc_init_IRQ () ; 
 int /*<<< orphan*/  arc_mmu_init () ; 
 int /*<<< orphan*/  arc_platform_smp_cpuinfo () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_arc_build_cfg_regs () ; 
 int smp_processor_id () ; 

void setup_processor(void)
{
	char str[512];
	int cpu_id = smp_processor_id();

	read_arc_build_cfg_regs();
	arc_init_IRQ();

	pr_info("%s", arc_cpu_mumbojumbo(cpu_id, str, sizeof(str)));

	arc_mmu_init();
	arc_cache_init();

	pr_info("%s", arc_extn_mumbojumbo(cpu_id, str, sizeof(str)));
	pr_info("%s", arc_platform_smp_cpuinfo());

	arc_chk_core_config();
}