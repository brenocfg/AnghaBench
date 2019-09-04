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
struct vm_area_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  octeon_flush_icache_all_cores (struct vm_area_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void octeon_flush_cache_sigtramp(unsigned long addr)
{
	struct vm_area_struct *vma;

	down_read(&current->mm->mmap_sem);
	vma = find_vma(current->mm, addr);
	octeon_flush_icache_all_cores(vma);
	up_read(&current->mm->mmap_sem);
}