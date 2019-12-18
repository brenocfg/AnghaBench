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
struct TYPE_2__ {int flags; } ;
struct mlx5_eswitch {TYPE_1__ fdb_table; } ;

/* Variables and functions */
 int ESW_FDB_CHAINS_AND_PRIOS_SUPPORTED ; 

bool mlx5_eswitch_prios_supported(struct mlx5_eswitch *esw)
{
	return (!!(esw->fdb_table.flags & ESW_FDB_CHAINS_AND_PRIOS_SUPPORTED));
}