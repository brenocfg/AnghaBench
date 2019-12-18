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
struct ion_system_heap {struct ion_page_pool** pools; } ;
struct ion_page_pool {int dummy; } ;
struct ion_buffer {int dummy; } ;

/* Variables and functions */
 struct page* ion_page_pool_alloc (struct ion_page_pool*) ; 
 size_t order_to_index (unsigned long) ; 

__attribute__((used)) static struct page *alloc_buffer_page(struct ion_system_heap *heap,
				      struct ion_buffer *buffer,
				      unsigned long order)
{
	struct ion_page_pool *pool = heap->pools[order_to_index(order)];

	return ion_page_pool_alloc(pool);
}