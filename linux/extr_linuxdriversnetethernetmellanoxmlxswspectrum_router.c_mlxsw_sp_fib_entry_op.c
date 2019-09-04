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
struct mlxsw_sp_fib_entry {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;

/* Variables and functions */
 int __mlxsw_sp_fib_entry_op (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_offload_refresh (struct mlxsw_sp_fib_entry*,int,int) ; 

__attribute__((used)) static int mlxsw_sp_fib_entry_op(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_fib_entry *fib_entry,
				 enum mlxsw_reg_ralue_op op)
{
	int err = __mlxsw_sp_fib_entry_op(mlxsw_sp, fib_entry, op);

	mlxsw_sp_fib_entry_offload_refresh(fib_entry, op, err);

	return err;
}