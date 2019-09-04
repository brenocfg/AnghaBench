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
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  show_lock ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sysrq_tlbdump_single(void *dummy)
{
	unsigned long flags;

	spin_lock_irqsave(&show_lock, flags);

	pr_info("CPU%d:\n", smp_processor_id());
	dump_tlb_regs();
	pr_info("\n");
	dump_tlb_all();
	pr_info("\n");

	spin_unlock_irqrestore(&show_lock, flags);
}