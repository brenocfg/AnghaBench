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
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages_lock ; 
 int free_pages_num ; 
 int /*<<< orphan*/  gnttab_free_pages (int,struct page**) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  scsiback_free_pages ; 
 int scsiback_max_buffer_pages ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void put_free_pages(struct page **page, int num)
{
	unsigned long flags;
	int i = free_pages_num + num, n = num;

	if (num == 0)
		return;
	if (i > scsiback_max_buffer_pages) {
		n = min(num, i - scsiback_max_buffer_pages);
		gnttab_free_pages(n, page + num - n);
		n = num - n;
	}
	spin_lock_irqsave(&free_pages_lock, flags);
	for (i = 0; i < n; i++)
		list_add(&page[i]->lru, &scsiback_free_pages);
	free_pages_num += n;
	spin_unlock_irqrestore(&free_pages_lock, flags);
}