#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; } ;
struct mlxsw_sp_fib4_entry {TYPE_1__ common; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP ; 
 int /*<<< orphan*/  mlxsw_sp_fib4_node_list_remove (struct mlxsw_sp_fib4_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_decap_fini (struct mlxsw_sp*,TYPE_1__*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_entry_del (struct mlxsw_sp*,TYPE_1__*) ; 

__attribute__((used)) static void
mlxsw_sp_fib4_node_entry_unlink(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_fib4_entry *fib4_entry)
{
	mlxsw_sp_fib_node_entry_del(mlxsw_sp, &fib4_entry->common);
	mlxsw_sp_fib4_node_list_remove(fib4_entry);

	if (fib4_entry->common.type == MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP)
		mlxsw_sp_fib_entry_decap_fini(mlxsw_sp, &fib4_entry->common);
}