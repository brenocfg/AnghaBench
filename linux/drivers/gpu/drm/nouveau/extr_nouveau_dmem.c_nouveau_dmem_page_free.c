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
struct page {struct nouveau_dmem_chunk* zone_device_data; } ;
struct nouveau_dmem_chunk {unsigned long pfn_first; int /*<<< orphan*/  lock; int /*<<< orphan*/  callocated; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nouveau_dmem_page_free(struct page *page)
{
	struct nouveau_dmem_chunk *chunk = page->zone_device_data;
	unsigned long idx = page_to_pfn(page) - chunk->pfn_first;

	/*
	 * FIXME:
	 *
	 * This is really a bad example, we need to overhaul nouveau memory
	 * management to be more page focus and allow lighter locking scheme
	 * to be use in the process.
	 */
	spin_lock(&chunk->lock);
	clear_bit(idx, chunk->bitmap);
	WARN_ON(!chunk->callocated);
	chunk->callocated--;
	/*
	 * FIXME when chunk->callocated reach 0 we should add the chunk to
	 * a reclaim list so that it can be freed in case of memory pressure.
	 */
	spin_unlock(&chunk->lock);
}