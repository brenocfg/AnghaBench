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
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  data_sm; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int dm_sm_inc_block (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_pool_inc_data_range(struct dm_pool_metadata *pmd, dm_block_t b, dm_block_t e)
{
	int r = 0;

	down_write(&pmd->root_lock);
	for (; b != e; b++) {
		r = dm_sm_inc_block(pmd->data_sm, b);
		if (r)
			break;
	}
	up_write(&pmd->root_lock);

	return r;
}