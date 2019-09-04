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
struct dm_btree_info {int /*<<< orphan*/  tm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btree_node_validator ; 
 int dm_tm_new_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 

int new_block(struct dm_btree_info *info, struct dm_block **result)
{
	return dm_tm_new_block(info->tm, &btree_node_validator, result);
}