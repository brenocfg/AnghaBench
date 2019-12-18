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
 int /*<<< orphan*/  flush_kernel_vmap_range (void*,size_t) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 

__attribute__((used)) static void persistent_memory_flush_cache(void *ptr, size_t size)
{
	if (is_vmalloc_addr(ptr))
		flush_kernel_vmap_range(ptr, size);
}