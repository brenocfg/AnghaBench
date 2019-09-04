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
struct dm_thin_device {int changed; int /*<<< orphan*/  mapped_blocks; int /*<<< orphan*/  id; struct dm_pool_metadata* pmd; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int dm_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __remove(struct dm_thin_device *td, dm_block_t block)
{
	int r;
	struct dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = { td->id, block };

	r = dm_btree_remove(&pmd->info, pmd->root, keys, &pmd->root);
	if (r)
		return r;

	td->mapped_blocks--;
	td->changed = 1;

	return 0;
}