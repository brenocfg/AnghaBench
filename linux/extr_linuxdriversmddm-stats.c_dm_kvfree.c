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
 int /*<<< orphan*/  free_shared_memory (size_t) ; 
 int /*<<< orphan*/  kvfree (void*) ; 

__attribute__((used)) static void dm_kvfree(void *ptr, size_t alloc_size)
{
	if (!ptr)
		return;

	free_shared_memory(alloc_size);

	kvfree(ptr);
}