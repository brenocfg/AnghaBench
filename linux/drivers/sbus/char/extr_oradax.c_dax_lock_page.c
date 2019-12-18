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
typedef  void page ;

/* Variables and functions */
 int /*<<< orphan*/  FOLL_WRITE ; 
 int /*<<< orphan*/  dax_dbg (char*,void*,...) ; 
 int get_user_pages_fast (unsigned long,int,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int dax_lock_page(void *va, struct page **p)
{
	int ret;

	dax_dbg("uva %p", va);

	ret = get_user_pages_fast((unsigned long)va, 1, FOLL_WRITE, p);
	if (ret == 1) {
		dax_dbg("locked page %p, for VA %p", *p, va);
		return 0;
	}

	dax_dbg("get_user_pages failed, va=%p, ret=%d", va, ret);
	return -1;
}