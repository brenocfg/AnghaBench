#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct ro_spine {int dummy; } ;
struct TYPE_2__ {size_t size; } ;
struct dm_btree_info {int levels; TYPE_1__ value_type; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENODATA ; 
 int btree_lookup_raw (struct ro_spine*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,void*,size_t) ; 
 int /*<<< orphan*/  exit_ro_spine (struct ro_spine*) ; 
 int /*<<< orphan*/  init_ro_spine (struct ro_spine*,struct dm_btree_info*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_bound ; 

int dm_btree_lookup(struct dm_btree_info *info, dm_block_t root,
		    uint64_t *keys, void *value_le)
{
	unsigned level, last_level = info->levels - 1;
	int r = -ENODATA;
	uint64_t rkey;
	__le64 internal_value_le;
	struct ro_spine spine;

	init_ro_spine(&spine, info);
	for (level = 0; level < info->levels; level++) {
		size_t size;
		void *value_p;

		if (level == last_level) {
			value_p = value_le;
			size = info->value_type.size;

		} else {
			value_p = &internal_value_le;
			size = sizeof(uint64_t);
		}

		r = btree_lookup_raw(&spine, root, keys[level],
				     lower_bound, &rkey,
				     value_p, size);

		if (!r) {
			if (rkey != keys[level]) {
				exit_ro_spine(&spine);
				return -ENODATA;
			}
		} else {
			exit_ro_spine(&spine);
			return r;
		}

		root = le64_to_cpu(internal_value_le);
	}
	exit_ro_spine(&spine);

	return r;
}