#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bits; } ;
struct TYPE_7__ {TYPE_1__ size; } ;
struct mlxsw_afk_element_inst {scalar_t__ type; TYPE_5__* info; TYPE_2__ item; } ;
struct mlxsw_afk_block {int instances_count; struct mlxsw_afk_element_inst* instances; } ;
struct mlxsw_afk {int blocks_count; struct mlxsw_afk_block* blocks; } ;
struct TYPE_8__ {scalar_t__ bits; } ;
struct TYPE_9__ {TYPE_3__ size; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_4__ item; } ;

/* Variables and functions */

__attribute__((used)) static bool mlxsw_afk_blocks_check(struct mlxsw_afk *mlxsw_afk)
{
	int i;
	int j;

	for (i = 0; i < mlxsw_afk->blocks_count; i++) {
		const struct mlxsw_afk_block *block = &mlxsw_afk->blocks[i];

		for (j = 0; j < block->instances_count; j++) {
			struct mlxsw_afk_element_inst *elinst;

			elinst = &block->instances[j];
			if (elinst->type != elinst->info->type ||
			    elinst->item.size.bits !=
			    elinst->info->item.size.bits)
				return false;
		}
	}
	return true;
}