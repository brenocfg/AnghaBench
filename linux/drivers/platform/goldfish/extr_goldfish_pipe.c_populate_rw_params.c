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
typedef  void* u64 ;
struct page {int dummy; } ;
struct TYPE_2__ {int* sizes; int buffers_count; void** ptrs; } ;
struct goldfish_pipe_command {TYPE_1__ rw_params; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 unsigned long page_to_phys (struct page*) ; 

__attribute__((used)) static void populate_rw_params(struct page **pages,
			       int pages_count,
			       unsigned long address,
			       unsigned long address_end,
			       unsigned long first_page,
			       unsigned long last_page,
			       unsigned int iter_last_page_size,
			       int is_write,
			       struct goldfish_pipe_command *command)
{
	/*
	 * Process the first page separately - it's the only page that
	 * needs special handling for its start address.
	 */
	unsigned long xaddr = page_to_phys(pages[0]);
	unsigned long xaddr_prev = xaddr;
	int buffer_idx = 0;
	int i = 1;
	int size_on_page = first_page == last_page
			? (int)(address_end - address)
			: (PAGE_SIZE - (address & ~PAGE_MASK));
	command->rw_params.ptrs[0] = (u64)(xaddr | (address & ~PAGE_MASK));
	command->rw_params.sizes[0] = size_on_page;
	for (; i < pages_count; ++i) {
		xaddr = page_to_phys(pages[i]);
		size_on_page = (i == pages_count - 1) ?
			iter_last_page_size : PAGE_SIZE;
		if (xaddr == xaddr_prev + PAGE_SIZE) {
			command->rw_params.sizes[buffer_idx] += size_on_page;
		} else {
			++buffer_idx;
			command->rw_params.ptrs[buffer_idx] = (u64)xaddr;
			command->rw_params.sizes[buffer_idx] = size_on_page;
		}
		xaddr_prev = xaddr;
	}
	command->rw_params.buffers_count = buffer_idx + 1;
}