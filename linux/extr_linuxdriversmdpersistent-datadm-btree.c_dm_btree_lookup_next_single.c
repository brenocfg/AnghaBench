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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct dm_btree_info {int /*<<< orphan*/  tm; TYPE_2__ value_type; } ;
struct dm_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  flags; } ;
struct btree_node {int /*<<< orphan*/ * keys; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int ENODATA ; 
 int INTERNAL_NODE ; 
 int bn_read_lock (struct dm_btree_info*,int /*<<< orphan*/ ,struct dm_block**) ; 
 struct btree_node* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int lower_bound (struct btree_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int upper_bound (struct btree_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value64 (struct btree_node*,int) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,int) ; 

__attribute__((used)) static int dm_btree_lookup_next_single(struct dm_btree_info *info, dm_block_t root,
				       uint64_t key, uint64_t *rkey, void *value_le)
{
	int r, i;
	uint32_t flags, nr_entries;
	struct dm_block *node;
	struct btree_node *n;

	r = bn_read_lock(info, root, &node);
	if (r)
		return r;

	n = dm_block_data(node);
	flags = le32_to_cpu(n->header.flags);
	nr_entries = le32_to_cpu(n->header.nr_entries);

	if (flags & INTERNAL_NODE) {
		i = lower_bound(n, key);
		if (i < 0) {
			/*
			 * avoid early -ENODATA return when all entries are
			 * higher than the search @key.
			 */
			i = 0;
		}
		if (i >= nr_entries) {
			r = -ENODATA;
			goto out;
		}

		r = dm_btree_lookup_next_single(info, value64(n, i), key, rkey, value_le);
		if (r == -ENODATA && i < (nr_entries - 1)) {
			i++;
			r = dm_btree_lookup_next_single(info, value64(n, i), key, rkey, value_le);
		}

	} else {
		i = upper_bound(n, key);
		if (i < 0 || i >= nr_entries) {
			r = -ENODATA;
			goto out;
		}

		*rkey = le64_to_cpu(n->keys[i]);
		memcpy(value_le, value_ptr(n, i), info->value_type.size);
	}
out:
	dm_tm_unlock(info->tm, node);
	return r;
}