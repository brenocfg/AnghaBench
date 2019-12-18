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
 int alloc_xenballooned_pages (int,struct page**) ; 
 int /*<<< orphan*/  gnttab_free_pages (int,struct page**) ; 
 int gnttab_pages_set_private (int,struct page**) ; 

int gnttab_alloc_pages(int nr_pages, struct page **pages)
{
	int ret;

	ret = alloc_xenballooned_pages(nr_pages, pages);
	if (ret < 0)
		return ret;

	ret = gnttab_pages_set_private(nr_pages, pages);
	if (ret < 0)
		gnttab_free_pages(nr_pages, pages);

	return ret;
}