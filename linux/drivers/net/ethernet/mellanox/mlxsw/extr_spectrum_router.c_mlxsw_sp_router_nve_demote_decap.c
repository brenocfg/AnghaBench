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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_fib_entry {int /*<<< orphan*/  type; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
typedef  enum mlxsw_sp_fib_entry_type { ____Placeholder_mlxsw_sp_fib_entry_type } mlxsw_sp_fib_entry_type ;

/* Variables and functions */
 int MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP ; 
 int /*<<< orphan*/  MLXSW_SP_FIB_ENTRY_TYPE_TRAP ; 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_update (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*) ; 
 struct mlxsw_sp_fib_entry* mlxsw_sp_router_ip2me_fib_entry_find (struct mlxsw_sp*,int /*<<< orphan*/ ,int,union mlxsw_sp_l3addr const*,int) ; 

void mlxsw_sp_router_nve_demote_decap(struct mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
				      enum mlxsw_sp_l3proto ul_proto,
				      const union mlxsw_sp_l3addr *ul_sip)
{
	enum mlxsw_sp_fib_entry_type type = MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP;
	struct mlxsw_sp_fib_entry *fib_entry;

	fib_entry = mlxsw_sp_router_ip2me_fib_entry_find(mlxsw_sp, ul_tb_id,
							 ul_proto, ul_sip,
							 type);
	if (!fib_entry)
		return;

	fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
	mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
}