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
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 scalar_t__ kmap_high (struct page*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 void* page_address (struct page*) ; 

void *kmap(struct page *page)
{
	unsigned long vaddr;
	might_sleep();
	if (!PageHighMem(page))
		return page_address(page);
	vaddr = (unsigned long)kmap_high(page);
	return (void *)vaddr;
}