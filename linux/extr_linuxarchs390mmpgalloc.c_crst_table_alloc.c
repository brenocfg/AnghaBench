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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arch_set_page_dat (struct page*,int) ; 
 scalar_t__ page_to_phys (struct page*) ; 

unsigned long *crst_table_alloc(struct mm_struct *mm)
{
	struct page *page = alloc_pages(GFP_KERNEL, 2);

	if (!page)
		return NULL;
	arch_set_page_dat(page, 2);
	return (unsigned long *) page_to_phys(page);
}