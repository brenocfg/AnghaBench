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
typedef  int /*<<< orphan*/  uint64_t ;
struct shadow_spine {TYPE_3__* info; } ;
struct dm_block {int dummy; } ;
struct TYPE_6__ {void* value_size; void* max_entries; void* nr_entries; void* flags; } ;
struct btree_node {int /*<<< orphan*/ * keys; TYPE_2__ header; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_5__ {int size; } ;
struct TYPE_7__ {int /*<<< orphan*/  tm; TYPE_1__ value_type; } ;

/* Variables and functions */
 int INTERNAL_NODE ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 int calc_max_entries (int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct btree_node* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_get_bm (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int new_block (TYPE_3__*,struct dm_block**) ; 
 struct dm_block* shadow_current (struct shadow_spine*) ; 
 int /*<<< orphan*/  unlock_block (TYPE_3__*,struct dm_block*) ; 
 int /*<<< orphan*/ * value_ptr (struct btree_node*,int) ; 

__attribute__((used)) static int btree_split_beneath(struct shadow_spine *s, uint64_t key)
{
	int r;
	size_t size;
	unsigned nr_left, nr_right;
	struct dm_block *left, *right, *new_parent;
	struct btree_node *pn, *ln, *rn;
	__le64 val;

	new_parent = shadow_current(s);

	pn = dm_block_data(new_parent);
	size = le32_to_cpu(pn->header.flags) & INTERNAL_NODE ?
		sizeof(__le64) : s->info->value_type.size;

	/* create & init the left block */
	r = new_block(s->info, &left);
	if (r < 0)
		return r;

	ln = dm_block_data(left);
	nr_left = le32_to_cpu(pn->header.nr_entries) / 2;

	ln->header.flags = pn->header.flags;
	ln->header.nr_entries = cpu_to_le32(nr_left);
	ln->header.max_entries = pn->header.max_entries;
	ln->header.value_size = pn->header.value_size;
	memcpy(ln->keys, pn->keys, nr_left * sizeof(pn->keys[0]));
	memcpy(value_ptr(ln, 0), value_ptr(pn, 0), nr_left * size);

	/* create & init the right block */
	r = new_block(s->info, &right);
	if (r < 0) {
		unlock_block(s->info, left);
		return r;
	}

	rn = dm_block_data(right);
	nr_right = le32_to_cpu(pn->header.nr_entries) - nr_left;

	rn->header.flags = pn->header.flags;
	rn->header.nr_entries = cpu_to_le32(nr_right);
	rn->header.max_entries = pn->header.max_entries;
	rn->header.value_size = pn->header.value_size;
	memcpy(rn->keys, pn->keys + nr_left, nr_right * sizeof(pn->keys[0]));
	memcpy(value_ptr(rn, 0), value_ptr(pn, nr_left),
	       nr_right * size);

	/* new_parent should just point to l and r now */
	pn->header.flags = cpu_to_le32(INTERNAL_NODE);
	pn->header.nr_entries = cpu_to_le32(2);
	pn->header.max_entries = cpu_to_le32(
		calc_max_entries(sizeof(__le64),
				 dm_bm_block_size(
					 dm_tm_get_bm(s->info->tm))));
	pn->header.value_size = cpu_to_le32(sizeof(__le64));

	val = cpu_to_le64(dm_block_location(left));
	__dm_bless_for_disk(&val);
	pn->keys[0] = ln->keys[0];
	memcpy_disk(value_ptr(pn, 0), &val, sizeof(__le64));

	val = cpu_to_le64(dm_block_location(right));
	__dm_bless_for_disk(&val);
	pn->keys[1] = rn->keys[0];
	memcpy_disk(value_ptr(pn, 1), &val, sizeof(__le64));

	unlock_block(s->info, left);
	unlock_block(s->info, right);
	return 0;
}