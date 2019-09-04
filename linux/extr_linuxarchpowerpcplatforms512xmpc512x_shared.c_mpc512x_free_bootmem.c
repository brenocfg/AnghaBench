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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PageTail (struct page*) ; 
 int /*<<< orphan*/  free_reserved_page (struct page*) ; 
 int page_ref_count (struct page*) ; 

__attribute__((used)) static inline void mpc512x_free_bootmem(struct page *page)
{
	BUG_ON(PageTail(page));
	BUG_ON(page_ref_count(page) > 1);
	free_reserved_page(page);
}