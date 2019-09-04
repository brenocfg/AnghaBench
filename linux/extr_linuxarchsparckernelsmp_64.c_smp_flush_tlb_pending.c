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
typedef  int /*<<< orphan*/  u32 ;
struct tlb_pending_info {unsigned long nr; unsigned long* vaddrs; int /*<<< orphan*/  ctx; } ;
struct mm_struct {int /*<<< orphan*/  mm_users; int /*<<< orphan*/  context; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_HWBITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_tlb_pending (int /*<<< orphan*/ ,unsigned long,unsigned long*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 TYPE_1__* current ; 
 int get_cpu () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_many (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tlb_pending_info*,int) ; 
 int /*<<< orphan*/  tlb_pending_func ; 

void smp_flush_tlb_pending(struct mm_struct *mm, unsigned long nr, unsigned long *vaddrs)
{
	u32 ctx = CTX_HWBITS(mm->context);
	struct tlb_pending_info info;
	int cpu = get_cpu();

	info.ctx = ctx;
	info.nr = nr;
	info.vaddrs = vaddrs;

	if (mm == current->mm && atomic_read(&mm->mm_users) == 1)
		cpumask_copy(mm_cpumask(mm), cpumask_of(cpu));
	else
		smp_call_function_many(mm_cpumask(mm), tlb_pending_func,
				       &info, 1);

	__flush_tlb_pending(ctx, nr, vaddrs);

	put_cpu();
}