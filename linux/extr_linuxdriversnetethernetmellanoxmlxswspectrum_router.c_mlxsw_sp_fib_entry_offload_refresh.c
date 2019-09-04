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
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;

/* Variables and functions */
#define  MLXSW_REG_RALUE_OP_WRITE_DELETE 129 
#define  MLXSW_REG_RALUE_OP_WRITE_WRITE 128 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_offload_set (struct mlxsw_sp_fib_entry*) ; 
 void mlxsw_sp_fib_entry_offload_unset (struct mlxsw_sp_fib_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_should_offload (struct mlxsw_sp_fib_entry*) ; 

__attribute__((used)) static void
mlxsw_sp_fib_entry_offload_refresh(struct mlxsw_sp_fib_entry *fib_entry,
				   enum mlxsw_reg_ralue_op op, int err)
{
	switch (op) {
	case MLXSW_REG_RALUE_OP_WRITE_DELETE:
		return mlxsw_sp_fib_entry_offload_unset(fib_entry);
	case MLXSW_REG_RALUE_OP_WRITE_WRITE:
		if (err)
			return;
		if (mlxsw_sp_fib_entry_should_offload(fib_entry))
			mlxsw_sp_fib_entry_offload_set(fib_entry);
		else
			mlxsw_sp_fib_entry_offload_unset(fib_entry);
		return;
	default:
		return;
	}
}