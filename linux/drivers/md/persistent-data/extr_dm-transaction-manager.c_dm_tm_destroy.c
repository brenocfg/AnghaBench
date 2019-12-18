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
struct dm_transaction_manager {int /*<<< orphan*/  is_clone; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dm_transaction_manager*) ; 
 int /*<<< orphan*/  wipe_shadow_table (struct dm_transaction_manager*) ; 

void dm_tm_destroy(struct dm_transaction_manager *tm)
{
	if (!tm->is_clone)
		wipe_shadow_table(tm);

	kfree(tm);
}