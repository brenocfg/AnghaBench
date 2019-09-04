#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cnapcr; int /*<<< orphan*/  cdozcr; } ;

/* Variables and functions */
#define  E500_PM_PH10 129 
#define  E500_PM_PH15 128 
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,unsigned int) ; 
 int get_hard_smp_processor_id (int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 TYPE_1__* rcpm_v1_regs ; 

__attribute__((used)) static void rcpm_v1_cpu_exit_state(int cpu, int state)
{
	int hw_cpu = get_hard_smp_processor_id(cpu);
	unsigned int mask = 1 << hw_cpu;

	switch (state) {
	case E500_PM_PH10:
		clrbits32(&rcpm_v1_regs->cdozcr, mask);
		break;
	case E500_PM_PH15:
		clrbits32(&rcpm_v1_regs->cnapcr, mask);
		break;
	default:
		pr_warn("Unknown cpu PM state (%d)\n", state);
		break;
	}
}