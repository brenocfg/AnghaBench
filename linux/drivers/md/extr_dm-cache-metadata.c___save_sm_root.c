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
struct dm_cache_metadata {int /*<<< orphan*/  metadata_space_map_root; int /*<<< orphan*/  metadata_sm; } ;

/* Variables and functions */
 int dm_sm_copy_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int dm_sm_root_size (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int __save_sm_root(struct dm_cache_metadata *cmd)
{
	int r;
	size_t metadata_len;

	r = dm_sm_root_size(cmd->metadata_sm, &metadata_len);
	if (r < 0)
		return r;

	return dm_sm_copy_root(cmd->metadata_sm, &cmd->metadata_space_map_root,
			       metadata_len);
}