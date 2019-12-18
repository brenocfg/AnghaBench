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
struct dm_transaction_manager {int /*<<< orphan*/  sm; int /*<<< orphan*/  is_clone; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_sm_dec_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dm_tm_dec(struct dm_transaction_manager *tm, dm_block_t b)
{
	/*
	 * The non-blocking clone doesn't support this.
	 */
	BUG_ON(tm->is_clone);

	dm_sm_dec_block(tm->sm, b);
}