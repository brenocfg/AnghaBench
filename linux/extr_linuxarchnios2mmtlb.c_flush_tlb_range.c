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
struct vm_area_struct {TYPE_1__* vm_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  flush_tlb_one_pid (unsigned long,unsigned long) ; 
 unsigned long get_pid_from_context (int /*<<< orphan*/ *) ; 

void flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			unsigned long end)
{
	unsigned long mmu_pid = get_pid_from_context(&vma->vm_mm->context);

	while (start < end) {
		flush_tlb_one_pid(start, mmu_pid);
		start += PAGE_SIZE;
	}
}