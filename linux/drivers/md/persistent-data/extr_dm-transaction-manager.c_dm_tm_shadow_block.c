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
struct dm_transaction_manager {int /*<<< orphan*/  bm; int /*<<< orphan*/  sm; scalar_t__ is_clone; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int __shadow_block (struct dm_transaction_manager*,int /*<<< orphan*/ ,struct dm_block_validator*,struct dm_block**) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int dm_bm_write_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_block_validator*,struct dm_block**) ; 
 int dm_sm_count_is_more_than_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  insert_shadow (struct dm_transaction_manager*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_shadow (struct dm_transaction_manager*,int /*<<< orphan*/ ) ; 

int dm_tm_shadow_block(struct dm_transaction_manager *tm, dm_block_t orig,
		       struct dm_block_validator *v, struct dm_block **result,
		       int *inc_children)
{
	int r;

	if (tm->is_clone)
		return -EWOULDBLOCK;

	r = dm_sm_count_is_more_than_one(tm->sm, orig, inc_children);
	if (r < 0)
		return r;

	if (is_shadow(tm, orig) && !*inc_children)
		return dm_bm_write_lock(tm->bm, orig, v, result);

	r = __shadow_block(tm, orig, v, result);
	if (r < 0)
		return r;
	insert_shadow(tm, dm_block_location(*result));

	return r;
}