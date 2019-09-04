#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* read_pic ) (int) ;int /*<<< orphan*/  (* read_pcr ) (int) ;} ;
struct TYPE_3__ {int num_pcrs; int num_pic_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_2__* pcr_ops ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int smp_processor_id () ; 
 TYPE_1__* sparc_pmu ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

void perf_event_print_debug(void)
{
	unsigned long flags;
	int cpu, i;

	if (!sparc_pmu)
		return;

	local_irq_save(flags);

	cpu = smp_processor_id();

	pr_info("\n");
	for (i = 0; i < sparc_pmu->num_pcrs; i++)
		pr_info("CPU#%d: PCR%d[%016llx]\n",
			cpu, i, pcr_ops->read_pcr(i));
	for (i = 0; i < sparc_pmu->num_pic_regs; i++)
		pr_info("CPU#%d: PIC%d[%016llx]\n",
			cpu, i, pcr_ops->read_pic(i));

	local_irq_restore(flags);
}