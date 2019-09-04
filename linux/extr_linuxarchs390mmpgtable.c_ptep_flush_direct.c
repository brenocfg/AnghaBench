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
struct TYPE_2__ {int /*<<< orphan*/  flush_count; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_TLB_LC ; 
 int _PAGE_INVALID ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_ipte_global (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptep_ipte_local (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline pte_t ptep_flush_direct(struct mm_struct *mm,
				      unsigned long addr, pte_t *ptep,
				      int nodat)
{
	pte_t old;

	old = *ptep;
	if (unlikely(pte_val(old) & _PAGE_INVALID))
		return old;
	atomic_inc(&mm->context.flush_count);
	if (MACHINE_HAS_TLB_LC &&
	    cpumask_equal(mm_cpumask(mm), cpumask_of(smp_processor_id())))
		ptep_ipte_local(mm, addr, ptep, nodat);
	else
		ptep_ipte_global(mm, addr, ptep, nodat);
	atomic_dec(&mm->context.flush_count);
	return old;
}