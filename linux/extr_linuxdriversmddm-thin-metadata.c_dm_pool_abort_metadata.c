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
struct dm_pool_metadata {int fail_io; int /*<<< orphan*/  root_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int __create_persistent_data_objects (struct dm_pool_metadata*,int) ; 
 int /*<<< orphan*/  __destroy_persistent_data_objects (struct dm_pool_metadata*) ; 
 int /*<<< orphan*/  __set_abort_with_changes_flags (struct dm_pool_metadata*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_pool_abort_metadata(struct dm_pool_metadata *pmd)
{
	int r = -EINVAL;

	down_write(&pmd->root_lock);
	if (pmd->fail_io)
		goto out;

	__set_abort_with_changes_flags(pmd);
	__destroy_persistent_data_objects(pmd);
	r = __create_persistent_data_objects(pmd, false);
	if (r)
		pmd->fail_io = true;

out:
	up_write(&pmd->root_lock);

	return r;
}