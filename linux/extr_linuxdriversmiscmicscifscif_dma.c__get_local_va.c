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
struct scif_window {int offset; scalar_t__ type; TYPE_1__* pinned_pages; } ;
struct page {int dummy; } ;
typedef  int off_t ;
struct TYPE_2__ {struct page** pages; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ SCIF_WINDOW_SELF ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static inline
void *_get_local_va(off_t off, struct scif_window *window, size_t len)
{
	int page_nr = (off - window->offset) >> PAGE_SHIFT;
	off_t page_off = off & ~PAGE_MASK;
	void *va = NULL;

	if (window->type == SCIF_WINDOW_SELF) {
		struct page **pages = window->pinned_pages->pages;

		va = page_address(pages[page_nr]) + page_off;
	}
	return va;
}