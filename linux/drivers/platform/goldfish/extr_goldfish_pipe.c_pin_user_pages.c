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
 int EFAULT ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int MAX_BUFFERS_PER_COMMAND ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int get_user_pages_fast (unsigned long,int,int /*<<< orphan*/ ,struct page**) ; 

__attribute__((used)) static int pin_user_pages(unsigned long first_page,
			  unsigned long last_page,
			  unsigned int last_page_size,
			  int is_write,
			  struct page *pages[MAX_BUFFERS_PER_COMMAND],
			  unsigned int *iter_last_page_size)
{
	int ret;
	int requested_pages = ((last_page - first_page) >> PAGE_SHIFT) + 1;

	if (requested_pages > MAX_BUFFERS_PER_COMMAND) {
		requested_pages = MAX_BUFFERS_PER_COMMAND;
		*iter_last_page_size = PAGE_SIZE;
	} else {
		*iter_last_page_size = last_page_size;
	}

	ret = get_user_pages_fast(first_page, requested_pages,
				  !is_write ? FOLL_WRITE : 0,
				  pages);
	if (ret <= 0)
		return -EFAULT;
	if (ret < requested_pages)
		*iter_last_page_size = PAGE_SIZE;

	return ret;
}