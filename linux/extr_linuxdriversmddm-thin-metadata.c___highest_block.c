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
struct dm_thin_device {int /*<<< orphan*/  id; struct dm_pool_metadata* pmd; } ;
struct dm_pool_metadata {int /*<<< orphan*/  bl_info; int /*<<< orphan*/  root; int /*<<< orphan*/  tl_info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int dm_btree_find_highest_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dm_btree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __highest_block(struct dm_thin_device *td, dm_block_t *result)
{
	int r;
	__le64 value_le;
	dm_block_t thin_root;
	struct dm_pool_metadata *pmd = td->pmd;

	r = dm_btree_lookup(&pmd->tl_info, pmd->root, &td->id, &value_le);
	if (r)
		return r;

	thin_root = le64_to_cpu(value_le);

	return dm_btree_find_highest_key(&pmd->bl_info, thin_root, result);
}