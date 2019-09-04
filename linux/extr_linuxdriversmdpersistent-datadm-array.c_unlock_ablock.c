#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tm; } ;
struct dm_array_info {TYPE_1__ btree_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 

__attribute__((used)) static void unlock_ablock(struct dm_array_info *info, struct dm_block *block)
{
	dm_tm_unlock(info->btree_info.tm, block);
}