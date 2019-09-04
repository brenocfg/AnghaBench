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
struct mlxsw_sp_ipip_entry {int dummy; } ;
struct mlxsw_sp_fib_entry {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_fib_entry* mlxsw_sp_ipip_entry_find_decap (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_entry_promote_decap (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*,struct mlxsw_sp_fib_entry*) ; 

__attribute__((used)) static void
mlxsw_sp_ipip_entry_ol_up_event(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_ipip_entry *ipip_entry)
{
	struct mlxsw_sp_fib_entry *decap_fib_entry;

	decap_fib_entry = mlxsw_sp_ipip_entry_find_decap(mlxsw_sp, ipip_entry);
	if (decap_fib_entry)
		mlxsw_sp_ipip_entry_promote_decap(mlxsw_sp, ipip_entry,
						  decap_fib_entry);
}