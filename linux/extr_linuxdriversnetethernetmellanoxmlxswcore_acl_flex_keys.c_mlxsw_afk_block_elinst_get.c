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
typedef  struct mlxsw_afk_element_inst {TYPE_1__* info; } const mlxsw_afk_element_inst ;
struct mlxsw_afk_block {int instances_count; struct mlxsw_afk_element_inst const* instances; } ;
typedef  enum mlxsw_afk_element { ____Placeholder_mlxsw_afk_element } mlxsw_afk_element ;
struct TYPE_2__ {int element; } ;

/* Variables and functions */

__attribute__((used)) static const struct mlxsw_afk_element_inst *
mlxsw_afk_block_elinst_get(const struct mlxsw_afk_block *block,
			   enum mlxsw_afk_element element)
{
	int i;

	for (i = 0; i < block->instances_count; i++) {
		struct mlxsw_afk_element_inst *elinst;

		elinst = &block->instances[i];
		if (elinst->info->element == element)
			return elinst;
	}
	return NULL;
}