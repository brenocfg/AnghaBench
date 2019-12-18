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
struct dm_clone_metadata {int /*<<< orphan*/  region_map; int /*<<< orphan*/  fail_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  __destroy_persistent_data_structures (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  dirty_map_exit (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  kfree (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

void dm_clone_metadata_close(struct dm_clone_metadata *cmd)
{
	if (!cmd->fail_io)
		__destroy_persistent_data_structures(cmd);

	dirty_map_exit(cmd);
	kvfree(cmd->region_map);
	kfree(cmd);
}