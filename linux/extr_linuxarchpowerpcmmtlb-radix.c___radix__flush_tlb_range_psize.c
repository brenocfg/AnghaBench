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
struct TYPE_3__ {unsigned long id; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_4__ {unsigned int shift; } ;

/* Variables and functions */
 unsigned long MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  RIC_FLUSH_ALL ; 
 int /*<<< orphan*/  RIC_FLUSH_TLB ; 
 unsigned long TLB_FLUSH_ALL ; 
 int /*<<< orphan*/  _tlbie_pid (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tlbie_va_range (unsigned long,unsigned long,unsigned long,unsigned long,int,int) ; 
 int /*<<< orphan*/  _tlbiel_pid (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tlbiel_va_range (unsigned long,unsigned long,unsigned long,unsigned long,int,int) ; 
 int /*<<< orphan*/  exit_flush_lazy_tlbs (struct mm_struct*) ; 
 int mm_is_singlethreaded (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_is_thread_local (struct mm_struct*) ; 
 scalar_t__ mm_needs_flush_escalation (struct mm_struct*) ; 
 TYPE_2__* mmu_psize_defs ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_mb () ; 
 unsigned long tlb_local_single_page_flush_ceiling ; 
 unsigned long tlb_single_page_flush_ceiling ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void __radix__flush_tlb_range_psize(struct mm_struct *mm,
				unsigned long start, unsigned long end,
				int psize, bool also_pwc)
{
	unsigned long pid;
	unsigned int page_shift = mmu_psize_defs[psize].shift;
	unsigned long page_size = 1UL << page_shift;
	unsigned long nr_pages = (end - start) >> page_shift;
	bool local, full;

	pid = mm->context.id;
	if (unlikely(pid == MMU_NO_CONTEXT))
		return;

	preempt_disable();
	smp_mb(); /* see radix__flush_tlb_mm */
	if (!mm_is_thread_local(mm)) {
		if (unlikely(mm_is_singlethreaded(mm))) {
			if (end != TLB_FLUSH_ALL) {
				exit_flush_lazy_tlbs(mm);
				goto is_local;
			}
		}
		local = false;
		full = (end == TLB_FLUSH_ALL ||
				nr_pages > tlb_single_page_flush_ceiling);
	} else {
is_local:
		local = true;
		full = (end == TLB_FLUSH_ALL ||
				nr_pages > tlb_local_single_page_flush_ceiling);
	}

	if (full) {
		if (local) {
			_tlbiel_pid(pid, also_pwc ? RIC_FLUSH_ALL : RIC_FLUSH_TLB);
		} else {
			if (mm_needs_flush_escalation(mm))
				also_pwc = true;

			_tlbie_pid(pid, also_pwc ? RIC_FLUSH_ALL : RIC_FLUSH_TLB);
		}
	} else {
		if (local)
			_tlbiel_va_range(start, end, pid, page_size, psize, also_pwc);
		else
			_tlbie_va_range(start, end, pid, page_size, psize, also_pwc);
	}
	preempt_enable();
}