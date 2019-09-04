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
struct dm_thin_lookup_result {int dummy; } ;
struct dm_thin_device {int /*<<< orphan*/  id; struct dm_pool_metadata* pmd; } ;
struct dm_btree_info {int dummy; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root; struct dm_btree_info nb_info; struct dm_btree_info info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int dm_btree_lookup (struct dm_btree_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_lookup_result (struct dm_thin_device*,int /*<<< orphan*/ ,struct dm_thin_lookup_result*) ; 

__attribute__((used)) static int __find_block(struct dm_thin_device *td, dm_block_t block,
			int can_issue_io, struct dm_thin_lookup_result *result)
{
	int r;
	__le64 value;
	struct dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = { td->id, block };
	struct dm_btree_info *info;

	if (can_issue_io) {
		info = &pmd->info;
	} else
		info = &pmd->nb_info;

	r = dm_btree_lookup(info, pmd->root, keys, &value);
	if (!r)
		unpack_lookup_result(td, value, result);

	return r;
}