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

/* Variables and functions */
 int /*<<< orphan*/  FOLL_WRITE ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int __get_user_pages_fast (unsigned long,int,int,struct page**) ; 
 int get_user_pages_unlocked (unsigned long,int,struct page**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 

int get_user_pages_fast(unsigned long start, int nr_pages, int write,
			struct page **pages)
{
	int nr, ret;

	might_sleep();
	start &= PAGE_MASK;
	nr = __get_user_pages_fast(start, nr_pages, write, pages);
	if (nr == nr_pages)
		return nr;

	/* Try to get the remaining pages with get_user_pages */
	start += nr << PAGE_SHIFT;
	pages += nr;
	ret = get_user_pages_unlocked(start, nr_pages - nr, pages,
				      write ? FOLL_WRITE : 0);
	/* Have to be a bit careful with return values */
	if (nr > 0)
		ret = (ret < 0) ? nr : ret + nr;
	return ret;
}