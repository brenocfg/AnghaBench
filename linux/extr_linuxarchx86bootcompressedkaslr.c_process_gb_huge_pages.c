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
struct mem_vector {unsigned long start; unsigned long size; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,unsigned long) ; 
 unsigned long PUD_SIZE ; 
 scalar_t__ max_gb_huge_pages ; 
 int /*<<< orphan*/  store_slot_info (struct mem_vector*,unsigned long) ; 

__attribute__((used)) static void
process_gb_huge_pages(struct mem_vector *region, unsigned long image_size)
{
	unsigned long addr, size = 0;
	struct mem_vector tmp;
	int i = 0;

	if (!max_gb_huge_pages) {
		store_slot_info(region, image_size);
		return;
	}

	addr = ALIGN(region->start, PUD_SIZE);
	/* Did we raise the address above the passed in memory entry? */
	if (addr < region->start + region->size)
		size = region->size - (addr - region->start);

	/* Check how many 1GB huge pages can be filtered out: */
	while (size > PUD_SIZE && max_gb_huge_pages) {
		size -= PUD_SIZE;
		max_gb_huge_pages--;
		i++;
	}

	/* No good 1GB huge pages found: */
	if (!i) {
		store_slot_info(region, image_size);
		return;
	}

	/*
	 * Skip those 'i'*1GB good huge pages, and continue checking and
	 * processing the remaining head or tail part of the passed region
	 * if available.
	 */

	if (addr >= region->start + image_size) {
		tmp.start = region->start;
		tmp.size = addr - region->start;
		store_slot_info(&tmp, image_size);
	}

	size  = region->size - (addr - region->start) - i * PUD_SIZE;
	if (size >= image_size) {
		tmp.start = addr + i * PUD_SIZE;
		tmp.size = size;
		store_slot_info(&tmp, image_size);
	}
}