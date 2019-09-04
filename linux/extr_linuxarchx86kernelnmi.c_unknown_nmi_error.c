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
struct TYPE_2__ {int /*<<< orphan*/  unknown; } ;

/* Variables and functions */
 int /*<<< orphan*/  NMI_UNKNOWN ; 
 int /*<<< orphan*/  __this_cpu_add (int /*<<< orphan*/ ,int) ; 
 int nmi_handle (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  nmi_panic (struct pt_regs*,char*) ; 
 TYPE_1__ nmi_stats ; 
 scalar_t__ panic_on_unrecovered_nmi ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unknown_nmi_panic ; 

__attribute__((used)) static void
unknown_nmi_error(unsigned char reason, struct pt_regs *regs)
{
	int handled;

	/*
	 * Use 'false' as back-to-back NMIs are dealt with one level up.
	 * Of course this makes having multiple 'unknown' handlers useless
	 * as only the first one is ever run (unless it can actually determine
	 * if it caused the NMI)
	 */
	handled = nmi_handle(NMI_UNKNOWN, regs);
	if (handled) {
		__this_cpu_add(nmi_stats.unknown, handled);
		return;
	}

	__this_cpu_add(nmi_stats.unknown, 1);

	pr_emerg("Uhhuh. NMI received for unknown reason %02x on CPU %d.\n",
		 reason, smp_processor_id());

	pr_emerg("Do you have a strange power saving mode enabled?\n");
	if (unknown_nmi_panic || panic_on_unrecovered_nmi)
		nmi_panic(regs, "NMI: Not continuing");

	pr_emerg("Dazed and confused, but trying to continue\n");
}