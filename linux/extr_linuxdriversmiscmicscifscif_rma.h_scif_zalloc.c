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

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 scalar_t__ MAX_ORDER ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,scalar_t__) ; 
 scalar_t__ get_order (size_t) ; 
 void* vzalloc (size_t) ; 

__attribute__((used)) static inline void *scif_zalloc(size_t size)
{
	void *ret = NULL;
	size_t align = ALIGN(size, PAGE_SIZE);

	if (align && get_order(align) < MAX_ORDER)
		ret = (void *)__get_free_pages(GFP_KERNEL | __GFP_ZERO,
					       get_order(align));
	return ret ? ret : vzalloc(align);
}