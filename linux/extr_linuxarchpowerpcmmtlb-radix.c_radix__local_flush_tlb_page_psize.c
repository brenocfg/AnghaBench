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
struct TYPE_2__ {unsigned long id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned long MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  _tlbiel_va (unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void radix__local_flush_tlb_page_psize(struct mm_struct *mm, unsigned long vmaddr,
				       int psize)
{
	unsigned long pid;

	preempt_disable();
	pid = mm->context.id;
	if (pid != MMU_NO_CONTEXT)
		_tlbiel_va(vmaddr, pid, psize, RIC_FLUSH_TLB);
	preempt_enable();
}