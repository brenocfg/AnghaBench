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
struct pool {int /*<<< orphan*/  pmd; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 scalar_t__ PM_OUT_OF_DATA_SPACE ; 
 int /*<<< orphan*/  PM_WRITE ; 
 int dm_pool_get_free_block_count (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ get_pool_mode (struct pool*) ; 
 int /*<<< orphan*/  requeue_bios (struct pool*) ; 
 int /*<<< orphan*/  set_pool_mode (struct pool*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_for_data_space(struct pool *pool)
{
	int r;
	dm_block_t nr_free;

	if (get_pool_mode(pool) != PM_OUT_OF_DATA_SPACE)
		return;

	r = dm_pool_get_free_block_count(pool->pmd, &nr_free);
	if (r)
		return;

	if (nr_free) {
		set_pool_mode(pool, PM_WRITE);
		requeue_bios(pool);
	}
}