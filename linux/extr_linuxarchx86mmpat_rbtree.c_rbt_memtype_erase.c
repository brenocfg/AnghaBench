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
typedef  scalar_t__ u64 ;
struct memtype {scalar_t__ start; scalar_t__ end; scalar_t__ subtree_max_end; int /*<<< orphan*/  rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct memtype* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMTYPE_END_MATCH ; 
 int /*<<< orphan*/  MEMTYPE_EXACT_MATCH ; 
 int /*<<< orphan*/  memtype_rb_augment_cb ; 
 int /*<<< orphan*/  memtype_rb_insert (int /*<<< orphan*/ *,struct memtype*) ; 
 struct memtype* memtype_rb_match (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memtype_rbroot ; 
 int /*<<< orphan*/  rb_erase_augmented (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct memtype *rbt_memtype_erase(u64 start, u64 end)
{
	struct memtype *data;

	/*
	 * Since the memtype_rbroot tree allows overlapping ranges,
	 * rbt_memtype_erase() checks with EXACT_MATCH first, i.e. free
	 * a whole node for the munmap case.  If no such entry is found,
	 * it then checks with END_MATCH, i.e. shrink the size of a node
	 * from the end for the mremap case.
	 */
	data = memtype_rb_match(&memtype_rbroot, start, end,
				MEMTYPE_EXACT_MATCH);
	if (!data) {
		data = memtype_rb_match(&memtype_rbroot, start, end,
					MEMTYPE_END_MATCH);
		if (!data)
			return ERR_PTR(-EINVAL);
	}

	if (data->start == start) {
		/* munmap: erase this node */
		rb_erase_augmented(&data->rb, &memtype_rbroot,
					&memtype_rb_augment_cb);
	} else {
		/* mremap: update the end value of this node */
		rb_erase_augmented(&data->rb, &memtype_rbroot,
					&memtype_rb_augment_cb);
		data->end = start;
		data->subtree_max_end = data->end;
		memtype_rb_insert(&memtype_rbroot, data);
		return NULL;
	}

	return data;
}