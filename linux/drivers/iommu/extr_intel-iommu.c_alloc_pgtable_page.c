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
 int GFP_ATOMIC ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 

void *alloc_pgtable_page(int node)
{
	struct page *page;
	void *vaddr = NULL;

	page = alloc_pages_node(node, GFP_ATOMIC | __GFP_ZERO, 0);
	if (page)
		vaddr = page_address(page);
	return vaddr;
}