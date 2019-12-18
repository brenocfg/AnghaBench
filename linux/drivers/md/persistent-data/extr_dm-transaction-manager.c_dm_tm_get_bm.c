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
struct dm_transaction_manager {struct dm_block_manager* bm; } ;
struct dm_block_manager {int dummy; } ;

/* Variables and functions */

struct dm_block_manager *dm_tm_get_bm(struct dm_transaction_manager *tm)
{
	return tm->bm;
}