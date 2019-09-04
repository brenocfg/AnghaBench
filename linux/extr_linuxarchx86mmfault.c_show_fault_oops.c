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
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int X86_CR4_SMEP ; 
 unsigned long X86_PF_INSTR ; 
 int _PAGE_USER ; 
 int __read_cr4 () ; 
 int /*<<< orphan*/ * __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  dump_pagetable (unsigned long) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/ * lookup_address_in_pgd (int /*<<< orphan*/ *,unsigned long,unsigned int*) ; 
 int /*<<< orphan*/  oops_may_print () ; 
 int pgd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_index (unsigned long) ; 
 int /*<<< orphan*/  pr_alert (char*,char*,void*) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_exec (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cr3_pa () ; 

__attribute__((used)) static void
show_fault_oops(struct pt_regs *regs, unsigned long error_code,
		unsigned long address)
{
	if (!oops_may_print())
		return;

	if (error_code & X86_PF_INSTR) {
		unsigned int level;
		pgd_t *pgd;
		pte_t *pte;

		pgd = __va(read_cr3_pa());
		pgd += pgd_index(address);

		pte = lookup_address_in_pgd(pgd, address, &level);

		if (pte && pte_present(*pte) && !pte_exec(*pte))
			pr_crit("kernel tried to execute NX-protected page - exploit attempt? (uid: %d)\n",
				from_kuid(&init_user_ns, current_uid()));
		if (pte && pte_present(*pte) && pte_exec(*pte) &&
				(pgd_flags(*pgd) & _PAGE_USER) &&
				(__read_cr4() & X86_CR4_SMEP))
			pr_crit("unable to execute userspace code (SMEP?) (uid: %d)\n",
				from_kuid(&init_user_ns, current_uid()));
	}

	pr_alert("BUG: unable to handle kernel %s at %px\n",
		 address < PAGE_SIZE ? "NULL pointer dereference" : "paging request",
		 (void *)address);

	dump_pagetable(address);
}