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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int VM_EXEC ; 
 int /*<<< orphan*/  __cpuc_coherent_kern_range (unsigned long,unsigned long) ; 

__attribute__((used)) static void flush_ptrace_access(struct vm_area_struct *vma, struct page *page,
			 unsigned long uaddr, void *kaddr, unsigned long len)
{
	/* VIPT non-aliasing D-cache */
	if (vma->vm_flags & VM_EXEC) {
		unsigned long addr = (unsigned long)kaddr;

		__cpuc_coherent_kern_range(addr, addr + len);
	}
}