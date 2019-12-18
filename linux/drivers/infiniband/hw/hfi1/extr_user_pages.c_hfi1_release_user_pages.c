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
struct mm_struct {int /*<<< orphan*/  pinned_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_sub (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_user_pages_dirty_lock (struct page**,size_t,int) ; 

void hfi1_release_user_pages(struct mm_struct *mm, struct page **p,
			     size_t npages, bool dirty)
{
	put_user_pages_dirty_lock(p, npages, dirty);

	if (mm) { /* during close after signal, mm can be NULL */
		atomic64_sub(npages, &mm->pinned_vm);
	}
}