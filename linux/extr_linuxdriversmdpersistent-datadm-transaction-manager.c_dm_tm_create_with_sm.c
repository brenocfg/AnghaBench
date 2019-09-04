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
struct dm_transaction_manager {int dummy; } ;
struct dm_space_map {int dummy; } ;
struct dm_block_manager {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int dm_tm_create_internal (struct dm_block_manager*,int /*<<< orphan*/ ,struct dm_transaction_manager**,struct dm_space_map**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dm_tm_create_with_sm(struct dm_block_manager *bm, dm_block_t sb_location,
			 struct dm_transaction_manager **tm,
			 struct dm_space_map **sm)
{
	return dm_tm_create_internal(bm, sb_location, tm, sm, 1, NULL, 0);
}