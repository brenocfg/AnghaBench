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
 int /*<<< orphan*/  binder_alloc_lru ; 
 int /*<<< orphan*/  binder_shrinker ; 
 int /*<<< orphan*/  list_lru_destroy (int /*<<< orphan*/ *) ; 
 int list_lru_init (int /*<<< orphan*/ *) ; 
 int register_shrinker (int /*<<< orphan*/ *) ; 

int binder_alloc_shrinker_init(void)
{
	int ret = list_lru_init(&binder_alloc_lru);

	if (ret == 0) {
		ret = register_shrinker(&binder_shrinker);
		if (ret)
			list_lru_destroy(&binder_alloc_lru);
	}
	return ret;
}