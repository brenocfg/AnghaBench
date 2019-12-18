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
struct vmballoon_batch_entry {int dummy; } ;
struct vmballoon {int batch_max_pages; int /*<<< orphan*/  batch_page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  static_branch_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_balloon_batching ; 

__attribute__((used)) static int vmballoon_init_batching(struct vmballoon *b)
{
	struct page *page;

	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page)
		return -ENOMEM;

	b->batch_page = page_address(page);
	b->batch_max_pages = PAGE_SIZE / sizeof(struct vmballoon_batch_entry);

	static_branch_enable(&vmw_balloon_batching);

	return 0;
}