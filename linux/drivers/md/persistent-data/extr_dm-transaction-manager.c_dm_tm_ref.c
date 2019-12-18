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
typedef  int /*<<< orphan*/  uint32_t ;
struct dm_transaction_manager {int /*<<< orphan*/  sm; scalar_t__ is_clone; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int dm_sm_get_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dm_tm_ref(struct dm_transaction_manager *tm, dm_block_t b,
	      uint32_t *result)
{
	if (tm->is_clone)
		return -EWOULDBLOCK;

	return dm_sm_get_count(tm->sm, b, result);
}