#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct shadow_spine {struct dm_block** nodes; TYPE_3__* info; } ;
struct dm_block {int dummy; } ;
struct TYPE_5__ {void* flags; int /*<<< orphan*/  value_size; int /*<<< orphan*/  max_entries; void* nr_entries; } ;
struct btree_node {int /*<<< orphan*/ * keys; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_6__ {int size; } ;
struct TYPE_7__ {TYPE_2__ value_type; } ;

/* Variables and functions */
 int INTERNAL_NODE ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct btree_node* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int insert_at (int,struct btree_node*,unsigned int,scalar_t__,int /*<<< orphan*/ *) ; 
 int le32_to_cpu (void*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int new_block (TYPE_3__*,struct dm_block**) ; 
 struct dm_block* shadow_current (struct shadow_spine*) ; 
 struct dm_block* shadow_parent (struct shadow_spine*) ; 
 int /*<<< orphan*/  unlock_block (TYPE_3__*,struct dm_block*) ; 
 int /*<<< orphan*/ * value_ptr (struct btree_node*,unsigned int) ; 

__attribute__((used)) static int btree_split_sibling(struct shadow_spine *s, unsigned parent_index,
			       uint64_t key)
{
	int r;
	size_t size;
	unsigned nr_left, nr_right;
	struct dm_block *left, *right, *parent;
	struct btree_node *ln, *rn, *pn;
	__le64 location;

	left = shadow_current(s);

	r = new_block(s->info, &right);
	if (r < 0)
		return r;

	ln = dm_block_data(left);
	rn = dm_block_data(right);

	nr_left = le32_to_cpu(ln->header.nr_entries) / 2;
	nr_right = le32_to_cpu(ln->header.nr_entries) - nr_left;

	ln->header.nr_entries = cpu_to_le32(nr_left);

	rn->header.flags = ln->header.flags;
	rn->header.nr_entries = cpu_to_le32(nr_right);
	rn->header.max_entries = ln->header.max_entries;
	rn->header.value_size = ln->header.value_size;
	memcpy(rn->keys, ln->keys + nr_left, nr_right * sizeof(rn->keys[0]));

	size = le32_to_cpu(ln->header.flags) & INTERNAL_NODE ?
		sizeof(uint64_t) : s->info->value_type.size;
	memcpy(value_ptr(rn, 0), value_ptr(ln, nr_left),
	       size * nr_right);

	/*
	 * Patch up the parent
	 */
	parent = shadow_parent(s);

	pn = dm_block_data(parent);
	location = cpu_to_le64(dm_block_location(left));
	__dm_bless_for_disk(&location);
	memcpy_disk(value_ptr(pn, parent_index),
		    &location, sizeof(__le64));

	location = cpu_to_le64(dm_block_location(right));
	__dm_bless_for_disk(&location);

	r = insert_at(sizeof(__le64), pn, parent_index + 1,
		      le64_to_cpu(rn->keys[0]), &location);
	if (r) {
		unlock_block(s->info, right);
		return r;
	}

	if (key < le64_to_cpu(rn->keys[0])) {
		unlock_block(s->info, right);
		s->nodes[1] = left;
	} else {
		unlock_block(s->info, left);
		s->nodes[1] = right;
	}

	return 0;
}