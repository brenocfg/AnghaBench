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
 int /*<<< orphan*/  dump_tlb_all () ; 
 int /*<<< orphan*/  dump_tlb_regs () ; 
 int /*<<< orphan*/  kvm_info (char*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void kvm_mips_dump_host_tlbs(void)
{
	unsigned long flags;

	local_irq_save(flags);

	kvm_info("HOST TLBs:\n");
	dump_tlb_regs();
	pr_info("\n");
	dump_tlb_all();

	local_irq_restore(flags);
}