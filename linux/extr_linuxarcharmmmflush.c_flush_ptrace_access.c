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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_mm; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int FLAG_PA_CORE_IN_MM ; 
 unsigned int FLAG_PA_IS_EXEC ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  __flush_ptrace_access (struct page*,unsigned long,void*,unsigned long,unsigned int) ; 
 scalar_t__ cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_cpumask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static
void flush_ptrace_access(struct vm_area_struct *vma, struct page *page,
			 unsigned long uaddr, void *kaddr, unsigned long len)
{
	unsigned int flags = 0;
	if (cpumask_test_cpu(smp_processor_id(), mm_cpumask(vma->vm_mm)))
		flags |= FLAG_PA_CORE_IN_MM;
	if (vma->vm_flags & VM_EXEC)
		flags |= FLAG_PA_IS_EXEC;
	__flush_ptrace_access(page, uaddr, kaddr, len, flags);
}