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
typedef  int /*<<< orphan*/  uint8_t ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  clflush_cache_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sev_clflush_pages(struct page *pages[], unsigned long npages)
{
	uint8_t *page_virtual;
	unsigned long i;

	if (npages == 0 || pages == NULL)
		return;

	for (i = 0; i < npages; i++) {
		page_virtual = kmap_atomic(pages[i]);
		clflush_cache_range(page_virtual, PAGE_SIZE);
		kunmap_atomic(page_virtual);
	}
}