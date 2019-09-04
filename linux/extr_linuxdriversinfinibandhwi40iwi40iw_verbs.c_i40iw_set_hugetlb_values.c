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
typedef  int /*<<< orphan*/  u64 ;
struct vm_area_struct {int dummy; } ;
struct i40iw_mr {int page_size; int /*<<< orphan*/  page_msk; } ;
struct hstate {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  huge_page_mask (struct hstate*) ; 
 int huge_page_size (struct hstate*) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_set_hugetlb_values(u64 addr, struct i40iw_mr *iwmr)
{
	struct vm_area_struct *vma;
	struct hstate *h;

	down_read(&current->mm->mmap_sem);
	vma = find_vma(current->mm, addr);
	if (vma && is_vm_hugetlb_page(vma)) {
		h = hstate_vma(vma);
		if (huge_page_size(h) == 0x200000) {
			iwmr->page_size = huge_page_size(h);
			iwmr->page_msk = huge_page_mask(h);
		}
	}
	up_read(&current->mm->mmap_sem);
}