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
typedef  int /*<<< orphan*/  uint64_t ;
struct ro_spine {int dummy; } ;
struct dm_btree_info {int levels; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  exit_ro_spine (struct ro_spine*) ; 
 int find_key (struct ro_spine*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_ro_spine (struct ro_spine*,struct dm_btree_info*) ; 

__attribute__((used)) static int dm_btree_find_key(struct dm_btree_info *info, dm_block_t root,
			     bool find_highest, uint64_t *result_keys)
{
	int r = 0, count = 0, level;
	struct ro_spine spine;

	init_ro_spine(&spine, info);
	for (level = 0; level < info->levels; level++) {
		r = find_key(&spine, root, find_highest, result_keys + level,
			     level == info->levels - 1 ? NULL : &root);
		if (r == -ENODATA) {
			r = 0;
			break;

		} else if (r)
			break;

		count++;
	}
	exit_ro_spine(&spine);

	return r ? r : count;
}