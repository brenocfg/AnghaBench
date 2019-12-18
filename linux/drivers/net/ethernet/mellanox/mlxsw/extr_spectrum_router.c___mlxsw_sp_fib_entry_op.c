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
struct mlxsw_sp_fib_entry {int type; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;

/* Variables and functions */
 int EINVAL ; 
#define  MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE 133 
#define  MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP 132 
#define  MLXSW_SP_FIB_ENTRY_TYPE_LOCAL 131 
#define  MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP 130 
#define  MLXSW_SP_FIB_ENTRY_TYPE_REMOTE 129 
#define  MLXSW_SP_FIB_ENTRY_TYPE_TRAP 128 
 int mlxsw_sp_fib_entry_op_blackhole (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int) ; 
 int mlxsw_sp_fib_entry_op_ipip_decap (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int) ; 
 int mlxsw_sp_fib_entry_op_local (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int) ; 
 int mlxsw_sp_fib_entry_op_nve_decap (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int) ; 
 int mlxsw_sp_fib_entry_op_remote (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int) ; 
 int mlxsw_sp_fib_entry_op_trap (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int) ; 

__attribute__((used)) static int __mlxsw_sp_fib_entry_op(struct mlxsw_sp *mlxsw_sp,
				   struct mlxsw_sp_fib_entry *fib_entry,
				   enum mlxsw_reg_ralue_op op)
{
	switch (fib_entry->type) {
	case MLXSW_SP_FIB_ENTRY_TYPE_REMOTE:
		return mlxsw_sp_fib_entry_op_remote(mlxsw_sp, fib_entry, op);
	case MLXSW_SP_FIB_ENTRY_TYPE_LOCAL:
		return mlxsw_sp_fib_entry_op_local(mlxsw_sp, fib_entry, op);
	case MLXSW_SP_FIB_ENTRY_TYPE_TRAP:
		return mlxsw_sp_fib_entry_op_trap(mlxsw_sp, fib_entry, op);
	case MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE:
		return mlxsw_sp_fib_entry_op_blackhole(mlxsw_sp, fib_entry, op);
	case MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP:
		return mlxsw_sp_fib_entry_op_ipip_decap(mlxsw_sp,
							fib_entry, op);
	case MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP:
		return mlxsw_sp_fib_entry_op_nve_decap(mlxsw_sp, fib_entry, op);
	}
	return -EINVAL;
}