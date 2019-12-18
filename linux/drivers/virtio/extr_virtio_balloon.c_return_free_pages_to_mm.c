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
struct virtio_balloon {unsigned long num_free_page_blocks; int /*<<< orphan*/  free_page_list_lock; int /*<<< orphan*/  free_page_list; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_BALLOON_FREE_PAGE_ORDER ; 
 struct page* balloon_page_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long return_free_pages_to_mm(struct virtio_balloon *vb,
					     unsigned long num_to_return)
{
	struct page *page;
	unsigned long num_returned;

	spin_lock_irq(&vb->free_page_list_lock);
	for (num_returned = 0; num_returned < num_to_return; num_returned++) {
		page = balloon_page_pop(&vb->free_page_list);
		if (!page)
			break;
		free_pages((unsigned long)page_address(page),
			   VIRTIO_BALLOON_FREE_PAGE_ORDER);
	}
	vb->num_free_page_blocks -= num_returned;
	spin_unlock_irq(&vb->free_page_list_lock);

	return num_returned;
}