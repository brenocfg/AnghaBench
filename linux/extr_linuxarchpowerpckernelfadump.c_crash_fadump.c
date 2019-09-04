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
struct pt_regs {int dummy; } ;
struct fadump_crash_info_header {int /*<<< orphan*/  online_mask; struct pt_regs regs; int /*<<< orphan*/  crashing_cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  fadumphdr_addr; scalar_t__ dump_registered; } ;

/* Variables and functions */
 struct fadump_crash_info_header* __va (int /*<<< orphan*/ ) ; 
 int cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * cpu_online_mask ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  crash_save_vmcoreinfo () ; 
 int /*<<< orphan*/  crashing_cpu ; 
 TYPE_1__ fw_dump ; 
 int /*<<< orphan*/  ppc_save_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  rtas_os_term (char*) ; 
 int /*<<< orphan*/  should_fadump_crash () ; 
 int smp_processor_id () ; 

void crash_fadump(struct pt_regs *regs, const char *str)
{
	struct fadump_crash_info_header *fdh = NULL;
	int old_cpu, this_cpu;

	if (!should_fadump_crash())
		return;

	/*
	 * old_cpu == -1 means this is the first CPU which has come here,
	 * go ahead and trigger fadump.
	 *
	 * old_cpu != -1 means some other CPU has already on it's way
	 * to trigger fadump, just keep looping here.
	 */
	this_cpu = smp_processor_id();
	old_cpu = cmpxchg(&crashing_cpu, -1, this_cpu);

	if (old_cpu != -1) {
		/*
		 * We can't loop here indefinitely. Wait as long as fadump
		 * is in force. If we race with fadump un-registration this
		 * loop will break and then we go down to normal panic path
		 * and reboot. If fadump is in force the first crashing
		 * cpu will definitely trigger fadump.
		 */
		while (fw_dump.dump_registered)
			cpu_relax();
		return;
	}

	fdh = __va(fw_dump.fadumphdr_addr);
	fdh->crashing_cpu = crashing_cpu;
	crash_save_vmcoreinfo();

	if (regs)
		fdh->regs = *regs;
	else
		ppc_save_regs(&fdh->regs);

	fdh->online_mask = *cpu_online_mask;

	/* Call ibm,os-term rtas call to trigger firmware assisted dump */
	rtas_os_term((char *)str);
}