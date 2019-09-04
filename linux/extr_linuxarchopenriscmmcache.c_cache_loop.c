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
 int L1_CACHE_BYTES ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  mtspr (unsigned int const,unsigned long) ; 
 unsigned long page_to_pfn (struct page*) ; 

__attribute__((used)) static void cache_loop(struct page *page, const unsigned int reg)
{
	unsigned long paddr = page_to_pfn(page) << PAGE_SHIFT;
	unsigned long line = paddr & ~(L1_CACHE_BYTES - 1);

	while (line < paddr + PAGE_SIZE) {
		mtspr(reg, line);
		line += L1_CACHE_BYTES;
	}
}