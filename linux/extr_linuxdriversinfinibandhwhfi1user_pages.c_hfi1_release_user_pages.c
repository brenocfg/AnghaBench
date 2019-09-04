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
struct mm_struct {size_t pinned_vm; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void hfi1_release_user_pages(struct mm_struct *mm, struct page **p,
			     size_t npages, bool dirty)
{
	size_t i;

	for (i = 0; i < npages; i++) {
		if (dirty)
			set_page_dirty_lock(p[i]);
		put_page(p[i]);
	}

	if (mm) { /* during close after signal, mm can be NULL */
		down_write(&mm->mmap_sem);
		mm->pinned_vm -= npages;
		up_write(&mm->mmap_sem);
	}
}