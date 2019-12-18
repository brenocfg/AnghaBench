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
 int /*<<< orphan*/  esw_put_prio_table (struct mlx5_eswitch*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void esw_destroy_offloads_fast_fdb_tables(struct mlx5_eswitch *esw)
{
	/* If lazy creation isn't supported, deref the fast path tables */
	if (!(esw->fdb_table.flags & ESW_FDB_CHAINS_AND_PRIOS_SUPPORTED)) {
		esw_put_prio_table(esw, 0, 1, 1);
		esw_put_prio_table(esw, 0, 1, 0);
	}
}