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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tunnel_index; } ;
struct mlxsw_sp_fib_entry {void* type; TYPE_1__ decap; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
typedef  enum mlxsw_sp_fib_entry_type { ____Placeholder_mlxsw_sp_fib_entry_type } mlxsw_sp_fib_entry_type ;

/* Variables and functions */
 void* MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP ; 
 void* MLXSW_SP_FIB_ENTRY_TYPE_TRAP ; 
 int mlxsw_sp_fib_entry_update (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*) ; 
 struct mlxsw_sp_fib_entry* mlxsw_sp_router_ip2me_fib_entry_find (struct mlxsw_sp*,int /*<<< orphan*/ ,int,union mlxsw_sp_l3addr const*,int) ; 

int mlxsw_sp_router_nve_promote_decap(struct mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
				      enum mlxsw_sp_l3proto ul_proto,
				      const union mlxsw_sp_l3addr *ul_sip,
				      u32 tunnel_index)
{
	enum mlxsw_sp_fib_entry_type type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
	struct mlxsw_sp_fib_entry *fib_entry;
	int err;

	/* It is valid to create a tunnel with a local IP and only later
	 * assign this IP address to a local interface
	 */
	fib_entry = mlxsw_sp_router_ip2me_fib_entry_find(mlxsw_sp, ul_tb_id,
							 ul_proto, ul_sip,
							 type);
	if (!fib_entry)
		return 0;

	fib_entry->decap.tunnel_index = tunnel_index;
	fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP;

	err = mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
	if (err)
		goto err_fib_entry_update;

	return 0;

err_fib_entry_update:
	fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
	mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
	return err;
}