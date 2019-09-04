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

/* Variables and functions */
 int EWOULDBLOCK ; 
 int dm_bm_flush (int /*<<< orphan*/ ) ; 
 int dm_sm_commit (int /*<<< orphan*/ ) ; 

int dm_tm_pre_commit(struct dm_transaction_manager *tm)
{
	int r;

	if (tm->is_clone)
		return -EWOULDBLOCK;

	r = dm_sm_commit(tm->sm);
	if (r < 0)
		return r;

	return dm_bm_flush(tm->bm);
}