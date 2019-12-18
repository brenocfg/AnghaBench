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
struct bnx2x_credit_pool_obj {int base_pool_offset; int /*<<< orphan*/ * pool_mirror; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_VEC64_CLEAR_BIT (int /*<<< orphan*/ *,int) ; 
 int BIT_VEC64_ELEM_SZ ; 
 scalar_t__ BIT_VEC64_TEST_BIT (int /*<<< orphan*/ *,int) ; 
 int BNX2X_POOL_VEC_SIZE ; 

__attribute__((used)) static bool bnx2x_credit_pool_get_entry(
	struct bnx2x_credit_pool_obj *o,
	int *offset)
{
	int idx, vec, i;

	*offset = -1;

	/* Find "internal cam-offset" then add to base for this object... */
	for (vec = 0; vec < BNX2X_POOL_VEC_SIZE; vec++) {

		/* Skip the current vector if there are no free entries in it */
		if (!o->pool_mirror[vec])
			continue;

		/* If we've got here we are going to find a free entry */
		for (idx = vec * BIT_VEC64_ELEM_SZ, i = 0;
		      i < BIT_VEC64_ELEM_SZ; idx++, i++)

			if (BIT_VEC64_TEST_BIT(o->pool_mirror, idx)) {
				/* Got one!! */
				BIT_VEC64_CLEAR_BIT(o->pool_mirror, idx);
				*offset = o->base_pool_offset + idx;
				return true;
			}
	}

	return false;
}