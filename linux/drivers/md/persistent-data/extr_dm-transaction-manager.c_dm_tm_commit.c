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
struct dm_transaction_manager {int /*<<< orphan*/  bm; scalar_t__ is_clone; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int dm_bm_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int /*<<< orphan*/  wipe_shadow_table (struct dm_transaction_manager*) ; 

int dm_tm_commit(struct dm_transaction_manager *tm, struct dm_block *root)
{
	if (tm->is_clone)
		return -EWOULDBLOCK;

	wipe_shadow_table(tm);
	dm_bm_unlock(root);

	return dm_bm_flush(tm->bm);
}