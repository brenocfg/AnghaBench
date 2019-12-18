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
struct mlxsw_afk {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear_block ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char*,int) ; 

void mlxsw_afk_clear(struct mlxsw_afk *mlxsw_afk, char *key,
		     int block_start, int block_end)
{
	int i;

	for (i = block_start; i <= block_end; i++)
		mlxsw_afk->ops->clear_block(key, i);
}