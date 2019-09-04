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

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  set_memory_x (unsigned long,int) ; 

__attribute__((used)) static void *alloc_dmainsn_page(void)
{
	void *page;

	page = (void *) __get_free_page(GFP_KERNEL | GFP_DMA);
	if (page)
		set_memory_x((unsigned long) page, 1);
	return page;
}