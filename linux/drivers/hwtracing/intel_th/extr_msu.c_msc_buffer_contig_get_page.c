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
struct msc {unsigned long nr_pages; scalar_t__ base; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 struct page* virt_to_page (scalar_t__) ; 

__attribute__((used)) static struct page *msc_buffer_contig_get_page(struct msc *msc,
					       unsigned long pgoff)
{
	if (pgoff >= msc->nr_pages)
		return NULL;

	return virt_to_page(msc->base + (pgoff << PAGE_SHIFT));
}