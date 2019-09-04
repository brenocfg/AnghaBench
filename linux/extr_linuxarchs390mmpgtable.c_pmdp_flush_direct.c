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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_TLB_LC ; 
 int _SEGMENT_ENTRY_INVALID ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmdp_idte_global (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmdp_idte_local (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static inline pmd_t pmdp_flush_direct(struct mm_struct *mm,
				      unsigned long addr, pmd_t *pmdp)
{
	pmd_t old;

	old = *pmdp;
	if (pmd_val(old) & _SEGMENT_ENTRY_INVALID)
		return old;
	atomic_inc(&mm->context.flush_count);
	if (MACHINE_HAS_TLB_LC &&
	    cpumask_equal(mm_cpumask(mm), cpumask_of(smp_processor_id())))
		pmdp_idte_local(mm, addr, pmdp);
	else
		pmdp_idte_global(mm, addr, pmdp);
	atomic_dec(&mm->context.flush_count);
	return old;
}