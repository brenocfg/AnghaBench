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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int flags; } ;
struct mlx5_eswitch {TYPE_1__ fdb_table; } ;

/* Variables and functions */
 int ESW_FDB_CHAINS_AND_PRIOS_SUPPORTED ; 
 int /*<<< orphan*/  FDB_MAX_CHAIN ; 

u32 mlx5_eswitch_get_chain_range(struct mlx5_eswitch *esw)
{
	if (esw->fdb_table.flags & ESW_FDB_CHAINS_AND_PRIOS_SUPPORTED)
		return FDB_MAX_CHAIN;

	return 0;
}