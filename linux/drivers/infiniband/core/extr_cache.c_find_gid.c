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
typedef  union ib_gid {int dummy; } ib_gid ;
struct ib_gid_attr {scalar_t__ gid_type; scalar_t__ ndev; int /*<<< orphan*/  gid; } ;
struct ib_gid_table_entry {struct ib_gid_attr attr; } ;
struct ib_gid_table {int sz; struct ib_gid_table_entry** data_vec; } ;

/* Variables and functions */
 unsigned long GID_ATTR_FIND_MASK_DEFAULT ; 
 unsigned long GID_ATTR_FIND_MASK_GID ; 
 unsigned long GID_ATTR_FIND_MASK_GID_TYPE ; 
 unsigned long GID_ATTR_FIND_MASK_NETDEV ; 
 scalar_t__ is_gid_entry_free (struct ib_gid_table_entry*) ; 
 int /*<<< orphan*/  is_gid_entry_valid (struct ib_gid_table_entry*) ; 
 int is_gid_index_default (struct ib_gid_table*,int) ; 
 scalar_t__ memcmp (union ib_gid const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int find_gid(struct ib_gid_table *table, const union ib_gid *gid,
		    const struct ib_gid_attr *val, bool default_gid,
		    unsigned long mask, int *pempty)
{
	int i = 0;
	int found = -1;
	int empty = pempty ? -1 : 0;

	while (i < table->sz && (found < 0 || empty < 0)) {
		struct ib_gid_table_entry *data = table->data_vec[i];
		struct ib_gid_attr *attr;
		int curr_index = i;

		i++;

		/* find_gid() is used during GID addition where it is expected
		 * to return a free entry slot which is not duplicate.
		 * Free entry slot is requested and returned if pempty is set,
		 * so lookup free slot only if requested.
		 */
		if (pempty && empty < 0) {
			if (is_gid_entry_free(data) &&
			    default_gid ==
				is_gid_index_default(table, curr_index)) {
				/*
				 * Found an invalid (free) entry; allocate it.
				 * If default GID is requested, then our
				 * found slot must be one of the DEFAULT
				 * reserved slots or we fail.
				 * This ensures that only DEFAULT reserved
				 * slots are used for default property GIDs.
				 */
				empty = curr_index;
			}
		}

		/*
		 * Additionally find_gid() is used to find valid entry during
		 * lookup operation; so ignore the entries which are marked as
		 * pending for removal and the entries which are marked as
		 * invalid.
		 */
		if (!is_gid_entry_valid(data))
			continue;

		if (found >= 0)
			continue;

		attr = &data->attr;
		if (mask & GID_ATTR_FIND_MASK_GID_TYPE &&
		    attr->gid_type != val->gid_type)
			continue;

		if (mask & GID_ATTR_FIND_MASK_GID &&
		    memcmp(gid, &data->attr.gid, sizeof(*gid)))
			continue;

		if (mask & GID_ATTR_FIND_MASK_NETDEV &&
		    attr->ndev != val->ndev)
			continue;

		if (mask & GID_ATTR_FIND_MASK_DEFAULT &&
		    is_gid_index_default(table, curr_index) != default_gid)
			continue;

		found = curr_index;
	}

	if (pempty)
		*pempty = empty;

	return found;
}