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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_file; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_tlb_page (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct hstate* hstate_file (int /*<<< orphan*/ ) ; 
 int huge_page_shift (struct hstate*) ; 

void flush_hugetlb_page(struct vm_area_struct *vma, unsigned long vmaddr)
{
	struct hstate *hstate = hstate_file(vma->vm_file);
	unsigned long tsize = huge_page_shift(hstate) - 10;

	__flush_tlb_page(vma->vm_mm, vmaddr, tsize, 0);
}