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
struct binder_buffer {void* data; } ;
struct binder_alloc {void* buffer; TYPE_1__* pages; } ;
struct TYPE_2__ {scalar_t__ page_ptr; int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 scalar_t__ PAGE_ALIGN (uintptr_t) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 

__attribute__((used)) static bool check_buffer_pages_allocated(struct binder_alloc *alloc,
					 struct binder_buffer *buffer,
					 size_t size)
{
	void *page_addr, *end;
	int page_index;

	end = (void *)PAGE_ALIGN((uintptr_t)buffer->data + size);
	page_addr = buffer->data;
	for (; page_addr < end; page_addr += PAGE_SIZE) {
		page_index = (page_addr - alloc->buffer) / PAGE_SIZE;
		if (!alloc->pages[page_index].page_ptr ||
		    !list_empty(&alloc->pages[page_index].lru)) {
			pr_err("expect alloc but is %s at page index %d\n",
			       alloc->pages[page_index].page_ptr ?
			       "lru" : "free", page_index);
			return false;
		}
	}
	return true;
}