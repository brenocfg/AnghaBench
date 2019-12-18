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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_fib_entry {TYPE_1__* nh_group; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_ralue_trap_action { ____Placeholder_mlxsw_reg_ralue_trap_action } mlxsw_reg_ralue_trap_action ;
typedef  enum mlxsw_reg_ralue_op { ____Placeholder_mlxsw_reg_ralue_op } mlxsw_reg_ralue_op ;
struct TYPE_2__ {int /*<<< orphan*/  ecmp_size; int /*<<< orphan*/  adj_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RALUE_LEN ; 
 int MLXSW_REG_RALUE_TRAP_ACTION_NOP ; 
 int MLXSW_REG_RALUE_TRAP_ACTION_TRAP ; 
 int /*<<< orphan*/  MLXSW_TRAP_ID_RTR_INGRESS0 ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_act_remote_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_entry_ralue_pack (char*,struct mlxsw_sp_fib_entry*,int) ; 
 scalar_t__ mlxsw_sp_fib_entry_should_offload (struct mlxsw_sp_fib_entry*) ; 
 int /*<<< orphan*/  ralue ; 

__attribute__((used)) static int mlxsw_sp_fib_entry_op_remote(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_fib_entry *fib_entry,
					enum mlxsw_reg_ralue_op op)
{
	char ralue_pl[MLXSW_REG_RALUE_LEN];
	enum mlxsw_reg_ralue_trap_action trap_action;
	u16 trap_id = 0;
	u32 adjacency_index = 0;
	u16 ecmp_size = 0;

	/* In case the nexthop group adjacency index is valid, use it
	 * with provided ECMP size. Otherwise, setup trap and pass
	 * traffic to kernel.
	 */
	if (mlxsw_sp_fib_entry_should_offload(fib_entry)) {
		trap_action = MLXSW_REG_RALUE_TRAP_ACTION_NOP;
		adjacency_index = fib_entry->nh_group->adj_index;
		ecmp_size = fib_entry->nh_group->ecmp_size;
	} else {
		trap_action = MLXSW_REG_RALUE_TRAP_ACTION_TRAP;
		trap_id = MLXSW_TRAP_ID_RTR_INGRESS0;
	}

	mlxsw_sp_fib_entry_ralue_pack(ralue_pl, fib_entry, op);
	mlxsw_reg_ralue_act_remote_pack(ralue_pl, trap_action, trap_id,
					adjacency_index, ecmp_size);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ralue), ralue_pl);
}