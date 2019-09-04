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
struct dm_thin_device {struct dm_pool_metadata* pmd; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  fail_io; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int __highest_block (struct dm_thin_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dm_thin_get_highest_mapped_block(struct dm_thin_device *td,
				     dm_block_t *result)
{
	int r = -EINVAL;
	struct dm_pool_metadata *pmd = td->pmd;

	down_read(&pmd->root_lock);
	if (!pmd->fail_io)
		r = __highest_block(td, result);
	up_read(&pmd->root_lock);

	return r;
}