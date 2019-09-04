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
struct thin_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  pmd; } ;
struct dm_thin_new_mapping {scalar_t__ data_block; scalar_t__ virt_end; scalar_t__ virt_begin; struct thin_c* tc; } ;
struct discard_op {int dummy; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  begin_discard (struct discard_op*,struct thin_c*,struct bio*) ; 
 int dm_pool_block_is_shared (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  end_discard (struct discard_op*,int) ; 
 int issue_discard (struct discard_op*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void passdown_double_checking_shared_status(struct dm_thin_new_mapping *m,
						   struct bio *discard_parent)
{
	/*
	 * We've already unmapped this range of blocks, but before we
	 * passdown we have to check that these blocks are now unused.
	 */
	int r = 0;
	bool shared = true;
	struct thin_c *tc = m->tc;
	struct pool *pool = tc->pool;
	dm_block_t b = m->data_block, e, end = m->data_block + m->virt_end - m->virt_begin;
	struct discard_op op;

	begin_discard(&op, tc, discard_parent);
	while (b != end) {
		/* find start of unmapped run */
		for (; b < end; b++) {
			r = dm_pool_block_is_shared(pool->pmd, b, &shared);
			if (r)
				goto out;

			if (!shared)
				break;
		}

		if (b == end)
			break;

		/* find end of run */
		for (e = b + 1; e != end; e++) {
			r = dm_pool_block_is_shared(pool->pmd, e, &shared);
			if (r)
				goto out;

			if (shared)
				break;
		}

		r = issue_discard(&op, b, e);
		if (r)
			goto out;

		b = e;
	}
out:
	end_discard(&op, r);
}