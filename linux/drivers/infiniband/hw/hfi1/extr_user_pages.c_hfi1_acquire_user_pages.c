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
 unsigned int FOLL_LONGTERM ; 
 unsigned int FOLL_WRITE ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int get_user_pages_fast (unsigned long,size_t,unsigned int,struct page**) ; 

int hfi1_acquire_user_pages(struct mm_struct *mm, unsigned long vaddr, size_t npages,
			    bool writable, struct page **pages)
{
	int ret;
	unsigned int gup_flags = FOLL_LONGTERM | (writable ? FOLL_WRITE : 0);

	ret = get_user_pages_fast(vaddr, npages, gup_flags, pages);
	if (ret < 0)
		return ret;

	atomic64_add(ret, &mm->pinned_vm);

	return ret;
}