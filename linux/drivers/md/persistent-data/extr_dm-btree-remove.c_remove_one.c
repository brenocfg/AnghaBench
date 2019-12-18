#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct shadow_spine {int dummy; } ;
struct dm_btree_value_type {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* dec ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dm_btree_info {int levels; TYPE_2__ value_type; int /*<<< orphan*/  tm; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_entries; } ;
struct btree_node {int /*<<< orphan*/ * keys; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  delete_at (struct btree_node*,int) ; 
 struct btree_node* dm_block_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_shadow_spine (struct shadow_spine*) ; 
 int /*<<< orphan*/  init_le64_type (int /*<<< orphan*/ ,struct dm_btree_value_type*) ; 
 int /*<<< orphan*/  init_shadow_spine (struct shadow_spine*,struct dm_btree_info*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int remove_nearest (struct shadow_spine*,struct dm_btree_info*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int remove_raw (struct shadow_spine*,struct dm_btree_info*,struct dm_btree_value_type*,int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  shadow_current (struct shadow_spine*) ; 
 int /*<<< orphan*/  shadow_root (struct shadow_spine*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value64 (struct btree_node*,int) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,int) ; 

__attribute__((used)) static int remove_one(struct dm_btree_info *info, dm_block_t root,
		      uint64_t *keys, uint64_t end_key,
		      dm_block_t *new_root, unsigned *nr_removed)
{
	unsigned level, last_level = info->levels - 1;
	int index = 0, r = 0;
	struct shadow_spine spine;
	struct btree_node *n;
	struct dm_btree_value_type le64_vt;
	uint64_t k;

	init_le64_type(info->tm, &le64_vt);
	init_shadow_spine(&spine, info);
	for (level = 0; level < last_level; level++) {
		r = remove_raw(&spine, info, &le64_vt,
			       root, keys[level], (unsigned *) &index);
		if (r < 0)
			goto out;

		n = dm_block_data(shadow_current(&spine));
		root = value64(n, index);
	}

	r = remove_nearest(&spine, info, &info->value_type,
			   root, keys[last_level], &index);
	if (r < 0)
		goto out;

	n = dm_block_data(shadow_current(&spine));

	if (index < 0)
		index = 0;

	if (index >= le32_to_cpu(n->header.nr_entries)) {
		r = -ENODATA;
		goto out;
	}

	k = le64_to_cpu(n->keys[index]);
	if (k >= keys[last_level] && k < end_key) {
		if (info->value_type.dec)
			info->value_type.dec(info->value_type.context,
					     value_ptr(n, index));

		delete_at(n, index);
		keys[last_level] = k + 1ull;

	} else
		r = -ENODATA;

out:
	*new_root = shadow_root(&spine);
	exit_shadow_spine(&spine);

	return r;
}