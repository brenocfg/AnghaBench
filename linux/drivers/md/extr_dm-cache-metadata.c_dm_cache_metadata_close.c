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
struct dm_cache_metadata {int /*<<< orphan*/  fail_io; int /*<<< orphan*/  list; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __destroy_persistent_data_objects (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  kfree (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_lock ; 

void dm_cache_metadata_close(struct dm_cache_metadata *cmd)
{
	if (refcount_dec_and_test(&cmd->ref_count)) {
		mutex_lock(&table_lock);
		list_del(&cmd->list);
		mutex_unlock(&table_lock);

		if (!cmd->fail_io)
			__destroy_persistent_data_objects(cmd);
		kfree(cmd);
	}
}