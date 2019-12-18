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
struct dm_cache_metadata {int /*<<< orphan*/  list; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  __destroy_persistent_data_objects (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  kfree (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dm_cache_metadata* lookup (struct block_device*) ; 
 struct dm_cache_metadata* metadata_open (struct block_device*,int /*<<< orphan*/ ,int,size_t,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table ; 
 int /*<<< orphan*/  table_lock ; 

__attribute__((used)) static struct dm_cache_metadata *lookup_or_open(struct block_device *bdev,
						sector_t data_block_size,
						bool may_format_device,
						size_t policy_hint_size,
						unsigned metadata_version)
{
	struct dm_cache_metadata *cmd, *cmd2;

	mutex_lock(&table_lock);
	cmd = lookup(bdev);
	mutex_unlock(&table_lock);

	if (cmd)
		return cmd;

	cmd = metadata_open(bdev, data_block_size, may_format_device,
			    policy_hint_size, metadata_version);
	if (!IS_ERR(cmd)) {
		mutex_lock(&table_lock);
		cmd2 = lookup(bdev);
		if (cmd2) {
			mutex_unlock(&table_lock);
			__destroy_persistent_data_objects(cmd);
			kfree(cmd);
			return cmd2;
		}
		list_add(&cmd->list, &table);
		mutex_unlock(&table_lock);
	}

	return cmd;
}