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
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  fail_io; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dm_pool_get_metadata_transaction_id(struct dm_pool_metadata *pmd,
					uint64_t *result)
{
	int r = -EINVAL;

	down_read(&pmd->root_lock);
	if (!pmd->fail_io) {
		*result = pmd->trans_id;
		r = 0;
	}
	up_read(&pmd->root_lock);

	return r;
}