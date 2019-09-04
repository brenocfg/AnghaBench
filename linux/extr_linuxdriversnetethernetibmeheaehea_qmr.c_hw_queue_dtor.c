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
struct hw_queue {int pagesize; int queue_length; scalar_t__* queue_pages; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 

__attribute__((used)) static void hw_queue_dtor(struct hw_queue *queue)
{
	int pages_per_kpage;
	int i, nr_pages;

	if (!queue || !queue->queue_pages)
		return;

	pages_per_kpage = PAGE_SIZE / queue->pagesize;

	nr_pages = queue->queue_length / queue->pagesize;

	for (i = 0; i < nr_pages; i += pages_per_kpage)
		free_page((unsigned long)(queue->queue_pages)[i]);

	kfree(queue->queue_pages);
}