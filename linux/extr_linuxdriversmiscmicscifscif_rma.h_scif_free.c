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
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static inline void scif_free(void *addr, size_t size)
{
	size_t align = ALIGN(size, PAGE_SIZE);

	if (is_vmalloc_addr(addr))
		vfree(addr);
	else
		free_pages((unsigned long)addr, get_order(align));
}