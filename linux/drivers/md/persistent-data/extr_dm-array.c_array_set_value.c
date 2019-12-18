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
typedef  unsigned int uint32_t ;
struct dm_btree_value_type {int /*<<< orphan*/  size; int /*<<< orphan*/  context; int /*<<< orphan*/  (* inc ) (int /*<<< orphan*/ ,void const*) ;int /*<<< orphan*/  (* dec ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* equal ) (int /*<<< orphan*/ ,void*,void const*) ;} ;
struct dm_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tm; } ;
struct dm_array_info {struct dm_btree_value_type value_type; TYPE_1__ btree_info; } ;
struct array_block {int /*<<< orphan*/  nr_entries; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int ENODATA ; 
 unsigned int calc_max_entries (int /*<<< orphan*/ ,size_t) ; 
 size_t dm_bm_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_get_bm (int /*<<< orphan*/ ) ; 
 void* element_at (struct dm_array_info*,struct array_block*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 int shadow_ablock (struct dm_array_info*,int /*<<< orphan*/ *,unsigned int,struct dm_block**,struct array_block**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,void const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  unlock_ablock (struct dm_array_info*,struct dm_block*) ; 

__attribute__((used)) static int array_set_value(struct dm_array_info *info, dm_block_t root,
			   uint32_t index, const void *value, dm_block_t *new_root)
{
	int r;
	struct dm_block *block;
	struct array_block *ab;
	size_t size_of_block;
	unsigned max_entries;
	unsigned entry;
	void *old_value;
	struct dm_btree_value_type *vt = &info->value_type;

	size_of_block = dm_bm_block_size(dm_tm_get_bm(info->btree_info.tm));
	max_entries = calc_max_entries(info->value_type.size, size_of_block);

	r = shadow_ablock(info, &root, index / max_entries, &block, &ab);
	if (r)
		return r;
	*new_root = root;

	entry = index % max_entries;
	if (entry >= le32_to_cpu(ab->nr_entries)) {
		r = -ENODATA;
		goto out;
	}

	old_value = element_at(info, ab, entry);
	if (vt->dec &&
	    (!vt->equal || !vt->equal(vt->context, old_value, value))) {
		vt->dec(vt->context, old_value);
		if (vt->inc)
			vt->inc(vt->context, value);
	}

	memcpy(old_value, value, info->value_type.size);

out:
	unlock_ablock(info, block);
	return r;
}