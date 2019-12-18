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
typedef  unsigned int uint32_t ;
struct dm_btree_value_type {int /*<<< orphan*/  size; int /*<<< orphan*/  context; int /*<<< orphan*/  (* inc ) (int /*<<< orphan*/ ,void const*) ;} ;
struct dm_array_info {struct dm_btree_value_type value_type; } ;
struct array_block {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  max_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  element_at (struct dm_array_info*,struct array_block*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static void fill_ablock(struct dm_array_info *info, struct array_block *ab,
			const void *value, unsigned new_nr)
{
	unsigned i;
	uint32_t nr_entries;
	struct dm_btree_value_type *vt = &info->value_type;

	BUG_ON(new_nr > le32_to_cpu(ab->max_entries));
	BUG_ON(new_nr < le32_to_cpu(ab->nr_entries));

	nr_entries = le32_to_cpu(ab->nr_entries);
	for (i = nr_entries; i < new_nr; i++) {
		if (vt->inc)
			vt->inc(vt->context, value);
		memcpy(element_at(info, ab, i), value, vt->size);
	}
	ab->nr_entries = cpu_to_le32(new_nr);
}