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
struct page {int dummy; } ;
struct mm_struct {int pinned_vm; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int get_user_pages_fast (unsigned long,size_t,int,struct page**) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int hfi1_acquire_user_pages(struct mm_struct *mm, unsigned long vaddr, size_t npages,
			    bool writable, struct page **pages)
{
	int ret;

	ret = get_user_pages_fast(vaddr, npages, writable, pages);
	if (ret < 0)
		return ret;

	down_write(&mm->mmap_sem);
	mm->pinned_vm += ret;
	up_write(&mm->mmap_sem);

	return ret;
}