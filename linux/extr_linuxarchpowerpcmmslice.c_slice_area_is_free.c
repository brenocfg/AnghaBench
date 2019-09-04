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
struct vm_area_struct {int dummy; } ;
struct TYPE_2__ {unsigned long slb_addr_limit; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned long vm_start_gap (struct vm_area_struct*) ; 

__attribute__((used)) static int slice_area_is_free(struct mm_struct *mm, unsigned long addr,
			      unsigned long len)
{
	struct vm_area_struct *vma;

	if ((mm->context.slb_addr_limit - len) < addr)
		return 0;
	vma = find_vma(mm, addr);
	return (!vma || (addr + len) <= vm_start_gap(vma));
}