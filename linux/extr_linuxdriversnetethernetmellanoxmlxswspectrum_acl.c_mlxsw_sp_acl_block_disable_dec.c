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
struct mlxsw_sp_acl_block {int /*<<< orphan*/  disable_count; } ;

/* Variables and functions */

void mlxsw_sp_acl_block_disable_dec(struct mlxsw_sp_acl_block *block)
{
	if (block)
		block->disable_count--;
}