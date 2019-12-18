#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_afa_block {TYPE_2__* first_set; } ;
struct TYPE_4__ {TYPE_1__* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  kvdl_index; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

u32 mlxsw_afa_block_first_kvdl_index(struct mlxsw_afa_block *block)
{
	/* First set is never in KVD linear. So the first set
	 * with valid KVD linear index is always the second one.
	 */
	if (WARN_ON(!block->first_set->next))
		return 0;
	return block->first_set->next->kvdl_index;
}