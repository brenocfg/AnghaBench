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
struct pt_regs {int /*<<< orphan*/ * areg; int /*<<< orphan*/  pc; } ;
struct exception_table_entry {int /*<<< orphan*/  fixup; } ;
struct TYPE_3__ {unsigned long bad_uaddr; } ;
struct TYPE_4__ {TYPE_1__ thread; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  do_exit (int) ; 
 int /*<<< orphan*/  pr_alert (char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct exception_table_entry* search_exception_tables (int /*<<< orphan*/ ) ; 

void
bad_page_fault(struct pt_regs *regs, unsigned long address, int sig)
{
	extern void die(const char*, struct pt_regs*, long);
	const struct exception_table_entry *entry;

	/* Are we prepared to handle this kernel fault?  */
	if ((entry = search_exception_tables(regs->pc)) != NULL) {
		pr_debug("%s: Exception at pc=%#010lx (%lx)\n",
			 current->comm, regs->pc, entry->fixup);
		current->thread.bad_uaddr = address;
		regs->pc = entry->fixup;
		return;
	}

	/* Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	pr_alert("Unable to handle kernel paging request at virtual "
		 "address %08lx\n pc = %08lx, ra = %08lx\n",
		 address, regs->pc, regs->areg[0]);
	die("Oops", regs, sig);
	do_exit(sig);
}