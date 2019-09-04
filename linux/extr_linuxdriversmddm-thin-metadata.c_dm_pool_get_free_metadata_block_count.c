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
struct dm_pool_metadata {scalar_t__ metadata_reserve; int /*<<< orphan*/  root_lock; int /*<<< orphan*/  metadata_sm; int /*<<< orphan*/  fail_io; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int dm_sm_get_nr_free (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dm_pool_get_free_metadata_block_count(struct dm_pool_metadata *pmd,
					  dm_block_t *result)
{
	int r = -EINVAL;

	down_read(&pmd->root_lock);
	if (!pmd->fail_io)
		r = dm_sm_get_nr_free(pmd->metadata_sm, result);

	if (!r) {
		if (*result < pmd->metadata_reserve)
			*result = 0;
		else
			*result -= pmd->metadata_reserve;
	}
	up_read(&pmd->root_lock);

	return r;
}