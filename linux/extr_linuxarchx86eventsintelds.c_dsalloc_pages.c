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
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 struct page* __alloc_pages_node (int,int,unsigned int) ; 
 int cpu_to_node (int) ; 
 unsigned int get_order (size_t) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static void *dsalloc_pages(size_t size, gfp_t flags, int cpu)
{
	unsigned int order = get_order(size);
	int node = cpu_to_node(cpu);
	struct page *page;

	page = __alloc_pages_node(node, flags | __GFP_ZERO, order);
	return page ? page_address(page) : NULL;
}