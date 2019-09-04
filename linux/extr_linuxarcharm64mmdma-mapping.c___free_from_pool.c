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
 int /*<<< orphan*/  __in_atomic_pool (void*,size_t) ; 
 int /*<<< orphan*/  atomic_pool ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,size_t) ; 

__attribute__((used)) static int __free_from_pool(void *start, size_t size)
{
	if (!__in_atomic_pool(start, size))
		return 0;

	gen_pool_free(atomic_pool, (unsigned long)start, size);

	return 1;
}