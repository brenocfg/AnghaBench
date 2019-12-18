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
 int /*<<< orphan*/  free_xenballooned_pages (int,struct page**) ; 
 int /*<<< orphan*/  gnttab_pages_clear_private (int,struct page**) ; 

void gnttab_free_pages(int nr_pages, struct page **pages)
{
	gnttab_pages_clear_private(nr_pages, pages);
	free_xenballooned_pages(nr_pages, pages);
}