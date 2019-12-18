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
struct buffer_head {struct buffer_head* b_this_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  __clear_page_buffers (struct page*) ; 
 int /*<<< orphan*/  free_buffer_head (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static void free_buffers(struct page *page)
{
	struct buffer_head *bh;

	if (!PagePrivate(page))
		return;

	bh = page_buffers(page);
	while (bh) {
		struct buffer_head *next = bh->b_this_page;
		free_buffer_head(bh);
		bh = next;
	}
	__clear_page_buffers(page);
	put_page(page);
}