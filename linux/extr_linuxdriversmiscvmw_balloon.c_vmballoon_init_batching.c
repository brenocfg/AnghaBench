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
struct vmballoon {int /*<<< orphan*/  batch_page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static bool vmballoon_init_batching(struct vmballoon *b)
{
	struct page *page;

	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page)
		return false;

	b->batch_page = page_address(page);
	return true;
}