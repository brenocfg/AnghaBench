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
struct dm_pool_metadata {int /*<<< orphan*/  root; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int dm_btree_lookup_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_lookup_result (struct dm_thin_device*,int /*<<< orphan*/ ,struct dm_thin_lookup_result*) ; 

__attribute__((used)) static int __find_next_mapped_block(struct dm_thin_device *td, dm_block_t block,
					  dm_block_t *vblock,
					  struct dm_thin_lookup_result *result)
{
	int r;
	__le64 value;
	struct dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = { td->id, block };

	r = dm_btree_lookup_next(&pmd->info, pmd->root, keys, vblock, &value);
	if (!r)
		unpack_lookup_result(td, value, result);

	return r;
}