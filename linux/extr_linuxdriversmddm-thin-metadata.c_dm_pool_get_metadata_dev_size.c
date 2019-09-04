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
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  metadata_sm; int /*<<< orphan*/  fail_io; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int dm_sm_get_nr_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dm_pool_get_metadata_dev_size(struct dm_pool_metadata *pmd,
				  dm_block_t *result)
{
	int r = -EINVAL;

	down_read(&pmd->root_lock);
	if (!pmd->fail_io)
		r = dm_sm_get_nr_blocks(pmd->metadata_sm, result);
	up_read(&pmd->root_lock);

	return r;
}