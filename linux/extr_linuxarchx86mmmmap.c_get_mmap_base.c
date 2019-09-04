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
struct mm_struct {unsigned long mmap_legacy_base; unsigned long mmap_base; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 

unsigned long get_mmap_base(int is_legacy)
{
	struct mm_struct *mm = current->mm;

#ifdef CONFIG_HAVE_ARCH_COMPAT_MMAP_BASES
	if (in_compat_syscall()) {
		return is_legacy ? mm->mmap_compat_legacy_base
				 : mm->mmap_compat_base;
	}
#endif
	return is_legacy ? mm->mmap_legacy_base : mm->mmap_base;
}