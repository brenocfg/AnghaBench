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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static void release_user_pages(struct page **pages, int pages_count,
			       int is_write, s32 consumed_size)
{
	int i;

	for (i = 0; i < pages_count; i++) {
		if (!is_write && consumed_size > 0)
			set_page_dirty(pages[i]);
		put_page(pages[i]);
	}
}